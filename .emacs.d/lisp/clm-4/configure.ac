# Configuration script for CLM (taken from Snd)

AC_INIT(CLM, 4, bil@ccrma.stanford.edu)
CLM_VERSION=4
AC_CONFIG_SRCDIR(clm.c)
AC_CANONICAL_HOST
AC_CONFIG_HEADERS(mus-config.h sndlib.h)
# no makefile -- actual compilation goes through all.lisp
AC_PROG_CC
AC_HEADER_STDC

audio_system="unknown"

#--------------------------------------------------------------------------------
# configuration options
#   --with-alsa           use ALSA (the default in Linux)
#   --with-oss            use OSS
#   --with-jack           use Jack
#   --with-static-alsa    use ALSA statically loaded (for RPM generation)
#   --with-esd            use Enlightened Sound Daemon
#   --with-static-gsl     try to statically load GSL
#   --with-modules        put sndlib names into modules
#--------------------------------------------------------------------------------

AC_ARG_WITH(esd,	[  --with-esd		  use ESD])
AC_ARG_WITH(oss,	[  --with-oss		  use OSS])
AC_ARG_WITH(alsa,	[  --with-alsa		  use ALSA])
AC_ARG_WITH(jack,       [  --with-jack		  use JACK])
AC_ARG_WITH(static-alsa,[  --with-static-alsa	  use ALSA statically loaded])
AC_ARG_WITH(modules,    [  --with-modules	  use if sndlib uses modules])



#--------------------------------------------------------------------------------
# standard libraries, header files, functions, OSS special cases
#--------------------------------------------------------------------------------

AC_PROG_INSTALL

AC_CHECK_LIB(m,main)
AC_CHECK_LIB(c,main)
AC_CHECK_LIB(dl,main)
LIBS=""

AC_CHECK_HEADERS(fcntl.h limits.h unistd.h string.h sys/soundcard.h machine/soundcard.h sys/mixer.h byteswap.h stdbool.h libc.h pthread.h)

AC_CHECK_HEADER(/usr/local/lib/oss/include/sys/soundcard.h,[AC_DEFINE(MUS_USR_LOCAL_LIB_OSS)])
AC_CHECK_HEADER(/usr/lib/oss/include/sys/soundcard.h,[AC_DEFINE(MUS_USR_LIB_OSS)])
AC_CHECK_HEADER(/opt/oss/include/sys/soundcard.h,[AC_DEFINE(MUS_OPT_OSS)])
AC_CHECK_HEADER(/var/lib/oss/include/sys/soundcard.h,[AC_DEFINE(MUS_VAR_LIB_OSS)])
AC_CHECK_HEADER(alsa/asoundlib.h,[AC_DEFINE(HAVE_ALSA_ASOUNDLIB_H)])

AC_TYPE_MODE_T
AC_TYPE_SIZE_T
AC_CHECK_TYPE(ssize_t, int)
AC_TYPE_PID_T
AC_OLD_BIGENDIAN
AC_TYPE_OFF_T
AC_SYS_LARGEFILE
AC_TYPE_INT64_T

AC_CHECK_SIZEOF(off_t)
AC_CHECK_SIZEOF(long)
AC_CHECK_SIZEOF(long long)
AC_CHECK_SIZEOF(unsigned long long)
AC_CHECK_SIZEOF(unsigned long)

# AC_CHECK_SIZEOF(void *)
# this won't work in version 2.66
AC_CHECK_SIZEOF(intptr_t)
AC_DEFINE_UNQUOTED(SIZEOF_VOID_P, $ac_cv_sizeof_intptr_t)

AC_CHECK_SIZEOF(int)
AC_CHECK_SIZEOF(int64_t)
AC_CHECK_SIZEOF(ssize_t)

AC_CHECK_DECLS(isnan,,,[#include <math.h>])
AC_CHECK_DECLS(isinf,,,[#include <math.h>])

AC_TYPE_SIGNAL
AC_CHECK_FUNCS(getcwd strerror access vsnprintf snprintf memmove strdup fileno strftime)

AC_DEFINE(HAVE_EXTENSION_LANGUAGE,0)

# check for pthreads 
AC_ARG_ENABLE(threads,
  [  --enable-threads      include pthread support],
  [
  if test "$enable_threads" = yes ; then
    if test "$ac_cv_header_pthread_h" = yes ; then
      AC_DEFINE(HAVE_PTHREADS)
#     CFLAGS="$CFLAGS -D_REENTRANT"
# what was this for?
      LIBS="$LIBS -lpthread"
    else
      AC_MSG_WARN([can't enable threads -- can't find pthread.h])
    fi]
  fi)

AC_PATH_PROG(PKG_CONFIG, pkg-config, no)


case "$host" in
    *-*-linux*) 
	AC_DEFINE(HAVE_LINUX)
	;;
    *-*-sunos4*) 
        AC_DEFINE(HAVE_SUN)
        ;;
    *-*-solaris*) 
	AC_DEFINE(HAVE_SUN)
        ;;
    *-*-netbsd*) 
        AC_DEFINE(HAVE_NETBSD)
        ;;
    *-*-cygwin*)
        AC_DEFINE(HAVE_WINDOZE)
	;;
    *-*-mingw*)
	AC_DEFINE(HAVE_WINDOZE)
	;;
    *-apple-*)
        AC_DEFINE(HAVE_OSX)
	;;
esac



#--------------------------------------------------------------------------------
# Audio library
#--------------------------------------------------------------------------------

AUDIO_LIB=""
LDSO_FLAGS=""
SO_FLAGS=""
SO_LD="ld"
SO_INSTALL="install"
A_LD="ld"
A_LD_FLAGS=""
LD_FLAGS="-r"

# we need the sndlib.h equivalents to try to find the native sound support (see config.guess)
# this only matters for those cases where we've implemented the audio code in audio.c
# test for ALSA courtesy of Paul Barton-Davis
# test for ESD courtesy of Nick Bailey
# test for BSD courtesy of Steven Schultz
# test for Jack courtesy of Kjetil S. Matheussen

JACK_LIBS=""
JACK_FLAGS=""

if test "$with_esd" = yes ; then
  AC_CHECK_LIB(esd,main,[
    AC_CHECK_HEADER(esd.h,
      [
	AC_DEFINE(MUS_ESD)
	esd_version="`esd-config --version`"
        AC_DEFINE_UNQUOTED(MUS_ESD_VERSION,"${esd_version}")
        audiofile_version="`audiofile-config --version`"
        AC_DEFINE_UNQUOTED(MUS_AUDIOFILE_VERSION,"${audiofile_version}")
        AUDIO_LIB="`esd-config --libs`"
#       ESD_CFLAGS="`esd-config --cflags`"
#	AC_SUBST(AUDIO_LIB)
        audio_system=ESD
      ],
      [AC_MSG_WARN(can't find the ESD header files)])],
    [AC_MSG_WARN(can't find the ESD library)])
fi

if test "$with_jack" = yes ; then 
            AC_CHECK_LIB(jack, main, [ 
	      AC_CHECK_HEADER(jack/jack.h, ,
   	          [with_jack=no
                   AC_MSG_WARN(can't find the JACK header files)])],
              [with_jack=no
	       AC_MSG_WARN(can't find the JACK library)])
            AC_CHECK_LIB(samplerate, main,[ 
	      AC_CHECK_HEADER(samplerate.h, ,
   	          [with_jack=no
                   AC_MSG_WARN(can't find the samplerate header files. JACK will not be used.)])],
              [with_jack=no
	       AC_MSG_WARN(can't find the samplerate library. JACK will not be used.)])
            if test $with_jack = yes ; then
               AUDIO_SYSTEM=JACK
	       AC_DEFINE(MUS_JACK)
	       AC_DEFINE(HAVE_JACK_IN_LINUX)
	       AC_DEFINE(HAVE_ALSA)
	       AUDIO_LIB="-lasound"
	       if test x$PKG_CONFIG != xno ; then
                   jack_version="`$PKG_CONFIG jack --modversion`"
                   AC_DEFINE_UNQUOTED(MUS_JACK_VERSION, "Jack: ${jack_version}")
          	   JACK_LIBS="`$PKG_CONFIG jack --libs`"
          	   JACK_FLAGS="`$PKG_CONFIG jack --cflags`"
               fi
            fi
fi

if test "$audio_system" != unknown ; then
  AC_MSG_RESULT(Using the $audio_system audio system)
else

case "$host" in
    *-*-linux*) 
	AC_DEFINE(MUS_LINUX)
        LDSO_FLAGS="-shared"
	if test "$GCC" = yes ; then
	  SO_FLAGS="-fPIC $SO_FLAGS"
        fi
        SO_LD="gcc"
	A_LD="ld"
#     This ^ used to be gcc, but that no longer seems to work
        LIBS="-L/usr/lib -lm"
#     This ^ used to be "" but in redhat 7 the -lm needs to be explicit for make sndsine etc
#     it was "" to cancel -lXpm without the needed -L<dir> for the same case
        audio_system=ALSA

	if test "$with_oss" = yes ; then 
          AUDIO_SYSTEM=OSS
	else
            AC_CHECK_LIB(asound,main,[ 
	      AC_CHECK_HEADER(sys/asoundlib.h,
                [audio_system=ALSA],
		[AC_CHECK_HEADER(alsa/asoundlib.h,
                    [audio_system=ALSA],
   	            [AC_MSG_WARN(can't find the ALSA header files)])])],
            [AC_MSG_WARN(can't find the ALSA library)])
        fi

	case $audio_system in
	    ALSA)
	    	AC_DEFINE(HAVE_ALSA)
		if test "$with_static_alsa" = yes ; then
                  AUDIO_LIB="/usr/lib/libasound.a"
		else
	    	  AUDIO_LIB="-lasound"
		fi
#	    	AC_SUBST(AUDIO_LIB)
# snd_config_get_id argnum changed in Nov-01
                snd_config_get_id_args=1
                AC_MSG_CHECKING([snd_config_get_id args])
                AC_COMPILE_IFELSE(
		  [AC_LANG_PROGRAM([#include <alsa/asoundlib.h>],
	          		   [snd_config_t *c; 
				    const char *id; 
		      		    snd_config_get_id(c, &id)])],
       		  snd_config_get_id_args=2)
                AC_MSG_RESULT($snd_config_get_id_args)
                AC_DEFINE_UNQUOTED(SND_CONFIG_GET_ID_ARGS,$snd_config_get_id_args)

                    AC_MSG_CHECKING([for newer alsa calling sequences])
                    AC_COMPILE_IFELSE(
		      [AC_LANG_PROGRAM([#include <alsa/asoundlib.h>],
	             		       [snd_pcm_hw_params_t *hw_params;
			  	        unsigned int tmp;
					int dir;
				        snd_pcm_hw_params_get_rate_max(hw_params, &tmp, &dir)
				       ])],
		       [AC_DEFINE(HAVE_NEW_ALSA)
                        AC_MSG_RESULT(yes)],
		       [AC_MSG_RESULT(no)])

		if test "$with_jack" = yes ; then 
		  if test "$with_static_alsa" = yes ; then
		    AUDIO_LIB="/usr/lib/libasound.a -ljack -l samplerate"
		  else
		    AUDIO_LIB="-lasound -ljack -lsamplerate"
                  fi
		 AC_DEFINE(HAVE_JACK)
 		fi
 		;;
	    JACK)
		AC_DEFINE(HAVE_JACK_IN_LINUX)
		AUDIO_LIB="-ljack -lsamplerate"
		;;
	    OSS)
		AC_DEFINE(HAVE_OSS)
		;;
	esac
	;;
    *-*-sunos4*) 
        AC_DEFINE(MUS_SUN)
	LIBS="-lm"
	audio_system=Sun
        ;;
    *-*-solaris*) 
	AC_DEFINE(MUS_SUN)
#	LIBS="-lm -ldl"
	LIBS="-lm"
	audio_system=Sun
	LDSO_FLAGS="-G"
        ;;
    *-*-hpux*) 
        AC_DEFINE(MUS_HPUX)
	audio_system=Hpux
	if test "$GCC" = yes ; then
	  SO_FLAGS="-fPIC $SO_FLAGS"
        fi
	LDSO_FLAGS="+z -Ae +DA1.1"
        ;;
    *-*-bsdi*) 
	AC_DEFINE(HAVE_OSS)
	LIBS="-lm"
	if test "$GCC" = yes ; then
	  SO_FLAGS="-fPIC $SO_FLAGS"
        fi
	audio_system=OSS
        ;;
    *-*-freebsd*)
	AC_DEFINE(HAVE_OSS)
	LIBS="-lm"
	audio_system=OSS
	if test "$GCC" = yes ; then
	  SO_FLAGS="-fPIC $SO_FLAGS"
        fi
        SO_LD="gcc -shared"
        A_LD="gcc"
	;;
    *-*-openbsd*) 
        AC_DEFINE(MUS_OPENBSD)
	audio_system=Sun
	if test "$GCC" = yes ; then
	  SO_FLAGS="-fPIC $SO_FLAGS"
        fi
        ;;
    *-*-netbsd*) 
        AC_DEFINE(MUS_NETBSD)
	audio_system=NetBSD
	if test "$GCC" = yes ; then
	  SO_FLAGS="-fPIC $SO_FLAGS"
        fi
	;;
    *-*-cygwin*)
	AC_DEFINE(MUS_WINDOZE)
	audio_system=Windoze
	;;
    *-apple-*)
        LDSO_FLAGS=""
	SO_INSTALL=":"
	SO_LD=":"
	AC_DEFINE(MUS_MAC_OSX)
	audio_system=MacOSX
	AUDIO_LIB="-framework CoreAudio -framework CoreFoundation -framework CoreMIDI"
#	AC_SUBST(AUDIO_LIB)

	    # OSX 10.5, deprecating earlier AudioDeviceRemoveIOProc
	    AC_MSG_CHECKING([for AudioDeviceDestroyIOProcID])
	    AC_COMPILE_IFELSE(
              [AC_LANG_PROGRAM([#include <CoreServices/CoreServices.h>
                                #include <CoreAudio/CoreAudio.h>],
			       [AudioDeviceIOProcID procId;
			        AudioDeviceID device = kAudioDeviceUnknown;
        			AudioDeviceDestroyIOProcID(device, procId)
			       ])],
	      [AC_DEFINE(HAVE_AUDIODEVICEDESTROYIOPROCID)
	       AC_MSG_RESULT(yes)],
	      [AC_MSG_RESULT(no)])

	AC_MSG_CHECKING([for kAudioDevicePropertyDeviceManufacturer])
	AC_COMPILE_IFELSE(
          [AC_LANG_PROGRAM([#include <CoreServices/CoreServices.h>
                            #include <CoreAudio/CoreAudio.h>],
			   [AudioDeviceID deviceID; 
			    UInt32 trans_size = 0, trans;
      			    trans_size = sizeof(UInt32);
     			    AudioDeviceGetProperty(deviceID, 0, true, kAudioDevicePropertyTransportType, &trans_size, &trans)
			   ])],
	  [AC_DEFINE(HAVE_KAUDIODEVICEPROPERTYTRANSPORTTYPE)
	   AC_MSG_RESULT(yes)],
	  [AC_MSG_RESULT(no)])
	AC_MSG_CHECKING([for kLinearPCMFormatFlagIsNonInterleaved])
	AC_COMPILE_IFELSE(
          [AC_LANG_PROGRAM([#include <CoreServices/CoreServices.h>
                            #include <CoreAudio/CoreAudio.h>],
			   [int i; i = kLinearPCMFormatFlagIsNonInterleaved])],
	  [AC_DEFINE(HAVE_KLINEARPCMFORMATFLAGISNONINTERLEAVED)
	   AC_MSG_RESULT(yes)],
	  [AC_MSG_RESULT(no)])
	;;
esac
AC_MSG_CHECKING([for audio system])
AC_MSG_RESULT($audio_system)
fi

CFLAGS="-I. $CFLAGS"
# needed since we're looking for <config.h>, I think

AC_SUBST(JACK_LIBS)
AC_SUBST(JACK_FLAGS)
AC_SUBST(AUDIO_LIB)

AC_SUBST(LDSO_FLAGS)
AC_SUBST(SO_FLAGS)
AC_SUBST(SO_INSTALL)
AC_SUBST(SO_LD)
AC_SUBST(A_LD)
AC_SUBST(A_LD_FLAGS)
AC_SUBST(LD_FLAGS)
AC_SUBST(SNDLIB_VERSION)
AC_SUBST(SNDLIB_LANGUAGE)
AC_SUBST(SNDLIB_MODULES)

AC_OUTPUT

