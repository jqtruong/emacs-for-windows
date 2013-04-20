/* mus-config.h.  Generated from mus-config.h.in by configure.  */
#ifndef CONFIG_H_LOADED
#define CONFIG_H_LOADED

#define RETSIGTYPE void

/* Define to `int' or something if <sys/types.h> doesn't define.  */
/* #undef mode_t */
/* #undef pid_t */
/* #undef size_t */
/* #undef ssize_t */
/* #undef off_t */

/* #undef WORDS_BIGENDIAN */

#define HAVE_GETCWD 1
#define HAVE_STRFTIME 1
#define HAVE_STRERROR 1
#define HAVE_ACCESS 1
#define HAVE_VSNPRINTF 1
#define HAVE_SNPRINTF 1
#define HAVE_MEMMOVE 1
#define HAVE_STRDUP 1
#define HAVE_FILENO 1

#define HAVE_DECL_ISNAN 1
#define HAVE_DECL_ISINF 1

#define STDC_HEADERS 1
#define HAVE_FCNTL_H 1
#define HAVE_LIMITS_H 1
#define HAVE_STRING_H 1
#define HAVE_UNISTD_H 1
#define HAVE_STDBOOL_H 1
/* #undef HAVE_SYS_SOUNDCARD_H */
/* #undef HAVE_MACHINE_SOUNDCARD_H */
/* #undef HAVE_SYS_MIXER_H */
/* #undef MUS_USR_LIB_OSS */
/* #undef MUS_USR_LOCAL_LIB_OSS */
/* #undef MUS_OPT_OSS */
/* #undef MUS_VAR_LIB_OSS */
#define HAVE_LIBC_H 1
/* #undef HAVE_ALSA_ASOUNDLIB_H */
/* #undef HAVE_BYTESWAP_H */

#define HAVE_PTHREAD_H 1
/* #undef HAVE_PTHREADS */

/* #undef _FILE_OFFSET_BITS */
/* #undef _LARGE_FILES */

#define SIZEOF_OFF_T 8
#define SIZEOF_LONG 8
#define SIZEOF_LONG_LONG 8
#define SIZEOF_UNSIGNED_LONG 8
#define SIZEOF_UNSIGNED_LONG_LONG 8
#define SIZEOF_VOID_P 8
#define SIZEOF_INT 4
#define SIZEOF_INT64_T 8
#define SIZEOF_SSIZE_T 8
#define SIZEOF_INTPTR_T 8


#define HAVE_OSX 1
/* #undef HAVE_WINDOZE */
/* #undef HAVE_SUN */
/* #undef HAVE_NETBSD */
/* #undef HAVE_LINUX */

/* #undef MUS_LINUX */
/* #undef MUS_HPUX */
/* #undef MUS_SUN */
/* #undef MUS_OPENBSD */
/* #undef MUS_WINDOZE */
/* #undef HAVE_OSS */
/* #undef HAVE_NEW_ALSA */
/* #undef HAVE_ALSA */
/* #undef HAVE_JACK_IN_LINUX */
/* #undef MUS_JACK */
/* #undef MUS_JACK_VERSION */
#define MUS_MAC_OSX 1
/* #undef MUS_ESD */
/* #undef MUS_NETBSD */
/* #undef MUS_PULSEAUDIO */
/* #undef MUS_PORTAUDIO */

/* #undef MUS_OUT_FORMAT */

#define HAVE_EXTENSION_LANGUAGE 0
/* #undef SND_CONFIG_GET_ID_ARGS */
/* #undef Float */
/* #undef MUS_AUDIOFILE_VERSION */
/* #undef WITH_MODULES */
#define HAVE_KAUDIODEVICEPROPERTYTRANSPORTTYPE 1
#define HAVE_KLINEARPCMFORMATFLAGISNONINTERLEAVED 1
#define HAVE_AUDIODEVICEDESTROYIOPROCID 1

#define USE_SND 0
#define CLM 1
#endif
