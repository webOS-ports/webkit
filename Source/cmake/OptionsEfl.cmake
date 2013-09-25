set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

add_definitions(-DBUILDING_EFL__=1)

if (NOT DEFINED ENABLE_WEBKIT2)
    set(ENABLE_WEBKIT2 ON)
endif ()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug" AND NOT SHARED_CORE)
    message(FATAL_ERROR "Turn on the SHARED_CORE flag to make a debug build - e.g.\n build-webkit --efl --debug --cmakeargs=\"-DSHARED_CORE=ON\".\n")
endif ()

find_package(Cairo 1.10.2 REQUIRED)
find_package(Fontconfig 2.8.0 REQUIRED)
find_package(Sqlite REQUIRED)
find_package(LibXml2 2.8.0 REQUIRED)
find_package(LibXslt 1.1.7 REQUIRED)
find_package(ICU REQUIRED)
find_package(Threads REQUIRED)
find_package(JPEG REQUIRED)
find_package(PNG REQUIRED)
find_package(ZLIB REQUIRED)

find_package(GLIB 2.36.0 REQUIRED COMPONENTS gio gobject gthread)
find_package(LibSoup 2.42.0 REQUIRED)

set(WTF_USE_ICU_UNICODE 1)
set(WTF_USE_SOUP 1)

add_definitions(-DWTF_USE_GLIB=1)
add_definitions(-DWTF_USE_SOUP=1)
add_definitions(-DWTF_USE_ICU_UNICODE=1)
add_definitions(-DWTF_USE_CAIRO=1)
add_definitions(-DWTF_USE_CROSS_PLATFORM_CONTEXT_MENUS=1)

set(WTF_OUTPUT_NAME wtf_efl)
set(JavaScriptCore_OUTPUT_NAME javascriptcore_efl)
set(WebCore_OUTPUT_NAME webcore_efl)
set(WebKit_OUTPUT_NAME ewebkit)
set(WebKit2_OUTPUT_NAME ewebkit2)

set(DATA_INSTALL_DIR "share/${WebKit_OUTPUT_NAME}-${PROJECT_VERSION_MAJOR}" CACHE PATH "Installation path for theme data")
set(THEME_BINARY_DIR ${CMAKE_BINARY_DIR}/WebCore/platform/efl/DefaultTheme)
file(MAKE_DIRECTORY ${THEME_BINARY_DIR})

add_definitions(-DDATA_DIR="${CMAKE_INSTALL_PREFIX}/${DATA_INSTALL_DIR}"
                -DTEST_THEME_DIR="${THEME_BINARY_DIR}")

set(VERSION_SCRIPT "-Wl,--version-script,${CMAKE_MODULE_PATH}/eflsymbols.filter")

WEBKIT_OPTION_BEGIN()
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_3D_RENDERING ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_ACCESSIBILITY ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_API_TESTS ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_BATTERY_STATUS ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_BLOB ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_CSS3_TEXT ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_CSS_DEVICE_ADAPTATION ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_CSS_IMAGE_SET ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_CSS_REGIONS ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_CSS_STICKY_POSITION ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_CSS_VARIABLES ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_CUSTOM_SCHEME_HANDLER ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_DATALIST_ELEMENT ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_DOM4_EVENTS_CONSTRUCTOR ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_DOWNLOAD_ATTRIBUTE ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_DRAG_SUPPORT ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_FAST_MOBILE_SCROLLING ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_FILTERS ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_FULLSCREEN_API ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_GAMEPAD ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_INDEXED_DATABASE ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_INPUT_TYPE_COLOR ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_LINK_PREFETCH ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_LLINT ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_MEDIA_CAPTURE ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_MEMORY_SAMPLER ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_MHTML ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_MOUSE_CURSOR_SCALE ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_NAVIGATOR_CONTENT_UTILS ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_NETSCAPE_PLUGIN_API ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_NETWORK_INFO ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_PAGE_VISIBILITY_API ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_RESOLUTION_MEDIA_QUERY ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_REQUEST_ANIMATION_FRAME ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_SECCOMP_FILTERS OFF)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_SHARED_WORKERS ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_SPELLCHECK ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_TEMPLATE_ELEMENT ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_TOUCH_EVENTS ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_USERSELECT_ALL ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_VIBRATION ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_VIDEO ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_VIDEO_TRACK ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_VIEW_MODE_CSS_MEDIA ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_WEB_AUDIO ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_WEB_TIMING ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_WEBGL ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_XHR_TIMEOUT ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(WTF_USE_TILED_BACKING_STORE ON)

# FIXME: Perhaps we need a more generic way of defining dependencies between features.
# VIDEO_TRACK depends on VIDEO.
if (NOT ENABLE_VIDEO AND ENABLE_VIDEO_TRACK)
    message(STATUS "Disabling VIDEO_TRACK since VIDEO support is disabled.")
    set(ENABLE_VIDEO_TRACK OFF)
endif ()
WEBKIT_OPTION_END()

option(ENABLE_ECORE_X "Enable Ecore_X specific usage (cursor, bell)" ON)
if (ENABLE_ECORE_X)
    # We need Xext.h to disable Xlib error messages  when running WTR on Xvfb.
    # These errors are dumped on stderr and makes the test driver thinks that
    # the test case has failed.
    find_package(X11 REQUIRED)

    list(APPEND ECORE_ADDITIONAL_COMPONENTS X)
    add_definitions(-DHAVE_ECORE_X)
    add_definitions(-DWTF_PLATFORM_X11=1)
    add_definitions(-DMOZ_X11)
endif ()

find_package(Eina 1.7 REQUIRED)
find_package(Evas 1.7 REQUIRED)
find_package(Ecore 1.7 COMPONENTS Evas File Input Imf Imf_Evas ${ECORE_ADDITIONAL_COMPONENTS})
find_package(Edje 1.7 REQUIRED)
find_package(Eet 1.7 REQUIRED)
find_package(Eeze 1.7 REQUIRED)
find_package(Efreet 1.7 REQUIRED)
find_package(E_DBus 1.7 COMPONENTS EUKit)

# Add Eo dependency if EFL version is 1.8
if (${EVAS_VERSION} VERSION_EQUAL 1.8 AND ${ECORE_VERSION} VERSION_EQUAL 1.8)
    find_package(Eo)
    add_definitions(-DWTF_USE_EO=1)
endif ()

find_package(Freetype 2.4.2 REQUIRED)
find_package(HarfBuzz 0.9.2 REQUIRED)
add_definitions(-DWTF_USE_FREETYPE=1)
add_definitions(-DWTF_USE_HARFBUZZ=1)

if (ENABLE_WEBKIT2 AND ENABLE_NETSCAPE_PLUGIN_API)
    set(ENABLE_PLUGIN_PROCESS 1)
endif ()

if (NOT ENABLE_SVG)
    set(ENABLE_SVG_FONTS 0)
endif ()

if (ENABLE_BATTERY_STATUS)
    find_package(DBus REQUIRED)
endif ()

if (ENABLE_VIDEO OR ENABLE_WEB_AUDIO)
    set(GSTREAMER_COMPONENTS app pbutils)
    set(WTF_USE_GSTREAMER 1)
    add_definitions(-DWTF_USE_GSTREAMER=1 -DGST_API_VERSION_1=1)

    if (ENABLE_VIDEO)
        list(APPEND GSTREAMER_COMPONENTS video)
    endif ()

    if (ENABLE_WEB_AUDIO)
        list(APPEND GSTREAMER_COMPONENTS audio fft)
        add_definitions(-DWTF_USE_WEBAUDIO_GSTREAMER=1)
    endif ()

    find_package(GStreamer 1.0.5 REQUIRED COMPONENTS ${GSTREAMER_COMPONENTS})
endif ()

if (WTF_USE_TILED_BACKING_STORE)
    add_definitions(-DWTF_USE_ACCELERATED_COMPOSITING=1)

    add_definitions(-DWTF_USE_COORDINATED_GRAPHICS=1)

    set(WTF_USE_TEXTURE_MAPPER 1)
    add_definitions(-DWTF_USE_TEXTURE_MAPPER=1)

    set(WTF_USE_3D_GRAPHICS 1)
    add_definitions(-DWTF_USE_3D_GRAPHICS=1)

    set(ENABLE_3D_RENDERING 1)
    add_definitions(-DENABLE_3D_RENDERING=1)
else ()
    # Disable 3D graphics and WEBGL if tiled backing is disabled
    set(ENABLE_WEBGL 0)
    set(WTF_USE_3D_GRAPHICS 0)
    add_definitions(-DWTF_USE_3D_GRAPHICS=0)
endif ()

if (ENABLE_WEBGL OR WTF_USE_TILED_BACKING_STORE)
    find_package(OpenGL REQUIRED)
    CHECK_INCLUDE_FILES("GL/glx.h" OPENGLX_FOUND)

    if (OPENGLX_FOUND)
        add_definitions(-DHAVE_GLX)
    endif ()

    option(ENABLE_EGL "Enable EGL Support")

    if (ENABLE_EGL)
        find_package(EGL REQUIRED)
    endif ()

    if (EGL_FOUND)
        set(WTF_USE_EGL 1)
        set(USE_GRAPHICS_SURFACE 1)
        add_definitions(-DWTF_USE_EGL=1)
        option(ENABLE_GLES2 "Enable GLES Support")

        if (ENABLE_GLES2)
            find_package(GLES REQUIRED)
        endif ()

        if (OPENGLES2_FOUND)
            set(WTF_USE_OPENGL_ES_2 1)
            add_definitions(-DWTF_USE_OPENGL_ES_2=1)
        endif ()
     elseif (OPENGLX_FOUND)
         add_definitions(-DWTF_USE_GLX=1)

         if (X11_Xcomposite_FOUND AND X11_Xrender_FOUND)
             set(USE_GRAPHICS_SURFACE 1)
         elseif (ENABLE_WEBGL)
             # FIXME: Add support for NOT X11_Xcomposite for GLX
             message(FATAL_ERROR "To use WebGL with GLX support requires X11_Xcomposite.")
         endif ()
    endif ()
endif ()

if (ENABLE_INSPECTOR)
    set(WEB_INSPECTOR_DIR "${DATA_INSTALL_DIR}/inspector")
    set(WEBINSPECTORUI_DIR "${CMAKE_SOURCE_DIR}/Source/WebInspectorUI")
    add_definitions(-DWEB_INSPECTOR_DIR=\"${CMAKE_BINARY_DIR}/${WEB_INSPECTOR_DIR}\")
    add_definitions(-DWEB_INSPECTOR_INSTALL_DIR=\"${CMAKE_INSTALL_PREFIX}/${WEB_INSPECTOR_DIR}\")
endif ()

if (ENABLE_SECCOMP_FILTERS)
    find_package(LibSeccomp REQUIRED)
endif ()

set(CPACK_SOURCE_GENERATOR TBZ2)

# Optimize binary size for release builds by removing dead sections on unix/gcc
if (CMAKE_COMPILER_IS_GNUCC AND UNIX AND NOT APPLE)
    set(CMAKE_C_FLAGS_RELEASE "-ffunction-sections -fdata-sections ${CMAKE_C_FLAGS_RELEASE}")
    set(CMAKE_CXX_FLAGS_RELEASE "-ffunction-sections -fdata-sections ${CMAKE_CXX_FLAGS_RELEASE}")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "-Wl,--gc-sections ${CMAKE_SHARED_LINKER_FLAGS_RELEASE}")
endif ()

if (ENABLE_WEBGL)
    set(ENABLE_WEBGL 1)
    if (USE_GRAPHICS_SURFACE)
        add_definitions(-DWTF_USE_GRAPHICS_SURFACE=1)
    endif ()
endif ()

if (ENABLE_SPELLCHECK)
    find_package(Enchant REQUIRED)
endif ()

if (ENABLE_ACCESSIBILITY)
    find_package(ATK 2.8.0 REQUIRED)
else ()
    add_definitions(-DHAVE_ACCESSIBILITY=0)
endif ()

if (ENABLE_INDEXED_DATABASE)
    set(WTF_USE_LEVELDB 1)
    add_definitions(-DWTF_USE_LEVELDB=1)
endif ()
