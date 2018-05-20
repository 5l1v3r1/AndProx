/*
 * This file is part of AndProx, an application for using Proxmark3 on Android.
 *
 * Copyright 2016-2017 Michael Farrell <micolous+git@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Under section 7 of the GNU General Public License v3, the following "further
 * restrictions" apply to this program:
 *
 *  (b) You must preserve reasonable legal notices and author attributions in
 *      the program.
 *  (c) You must not misrepresent the origin of this program, and need to mark
 *      modified versions in reasonable ways as different from the original
 *      version (such as changing the name and logos).
 *  (d) You may not use the names of licensors or authors for publicity
 *      purposes, without explicit written permission.
 */

#include "uart_android.h"
#include "natives.h"
#include <uart.h>
#include <jni.h>

/**
 * Dummy function for OpenProxmark. We need to be able to throw different parameters for Android's
 * implementation, because we don't actually have a path to a port. This simply returns the given
 * "port name", so that OpenProxmark will set the internal serial port structure appropriately.
 *
 * We already are presumed to have handled a number of connection-related errors before actually
 * calling OpenProxmark, so this does ~nothing.
 * @param pcPortName Pointer to an opened serial_port_android
 * @return
 */
serial_port uart_open(const char* pcPortName) {
    return (serial_port)pcPortName;
}

serial_port uart_open_android(JNIEnv* env, JavaVM* vm, jobject nsw)
{
    serial_port_android* sp = malloc(sizeof(serial_port_android));
    sp->javaVM = vm;
    sp->nativeSerialWrapper = (*env)->NewGlobalRef(env, nsw);
    return sp;
}

void uart_close(const serial_port sp) {
    serial_port_android* spa = (serial_port_android*)sp;
    //PrintAndLog("uart_close()");
    if (spa == NULL) return;
    GET_ENV(spa->javaVM)
    if (env == NULL) return;

    (*env)->CallVoidMethod(env, spa->nativeSerialWrapper, g_ctx.jmNSWClose);
    (*env)->DeleteGlobalRef(env, spa->nativeSerialWrapper);
    free(spa);
}

bool uart_receive(const serial_port sp, uint8_t* pbtRx, size_t pszMaxRxLen, size_t* pszRxLen) {
    serial_port_android* spa = (serial_port_android*)sp;
    //PrintAndLog("uart_recieve(%d)", pszMaxRxLen);
    if (spa == NULL) return false;
    GET_ENV(spa->javaVM)
    if (env == NULL) return false;

    // Make a new buffer for Java to use
    jbyteArray recvBuffer = (*env)->NewByteArray(env, (jsize)pszMaxRxLen);

    jint ret = (*env)->CallIntMethod(env, spa->nativeSerialWrapper, g_ctx.jmNSWReceive, recvBuffer);

    if (ret <= 0) {
        // We got an error or no data
        *pszRxLen = 0;
        (*env)->DeleteLocalRef(env, recvBuffer);
        return false;
    }

    // We got a response, copy the buffer
    if (ret > SIZE_MAX) {
        ret = (jint)pszMaxRxLen;
    }

    if (ret > pszMaxRxLen) {
        *pszRxLen = (size_t)ret;
    } else {
        *pszRxLen = pszMaxRxLen;
    }

    (*env)->GetByteArrayRegion(env, recvBuffer, 0, (jsize)*pszRxLen, (jbyte*)pbtRx);

    (*env)->DeleteLocalRef(env, recvBuffer);
    return true;
}

bool uart_send(const serial_port sp, const uint8_t* pbtTx, const size_t szTxLen) {
    serial_port_android* spa = (serial_port_android*)sp;
    //PrintAndLog("uart_send(%d)", szTxLen);
    if (spa == NULL) return false;
    GET_ENV(spa->javaVM)
    if (env == NULL) return false;

    // Make a new buffer for Java to use
    jbyteArray sendBuffer = (*env)->NewByteArray(env, (jsize)szTxLen);
    (*env)->SetByteArrayRegion(env, sendBuffer, 0, (jsize)szTxLen, (const jbyte*)pbtTx);

    jboolean ret = (*env)->CallBooleanMethod(env, spa->nativeSerialWrapper, g_ctx.jmNSWSend, sendBuffer);

    (*env)->DeleteLocalRef(env, sendBuffer);

    return ret == JNI_TRUE;
}

bool uart_set_speed(serial_port sp, const uint32_t uiPortSpeed) {
    // Does nothing.
    return true;
}

uint32_t uart_get_speed(const serial_port sp) {
    // Fake.
    return 115200;
}
