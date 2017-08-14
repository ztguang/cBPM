/*
 * Copyright (c) 1996, 1998, Oracle and/or its affiliates. All rights reserved.
 * ORACLE PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
#include <sys/types.h>          //ztg add

#ifndef _JAVASOFT_JNI_MD_H_
#define _JAVASOFT_JNI_MD_H_

//#define JNIEXPORT __declspec(dllexport)       //ztg delete
//#define JNIIMPORT __declspec(dllimport)       //ztg delete
#define JNIEXPORT __attribute__ ((visibility("default")))
#define JNIIMPORT __attribute__ ((visibility("default")))

//JNICALL是JAVA调用本地方法时，用C/C++写的本地方法库中的函数导出方式，是一个C/C++里的宏：
//#define JNICALL __stdcall       //ztg delete
#define JNICALL

typedef long jint;
//typedef __int64 jlong;      //ztg delete
typedef int64_t jlong;

typedef signed char jbyte;

#endif /* !_JAVASOFT_JNI_MD_H_ */
