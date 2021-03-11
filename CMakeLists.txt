cmake_minimum_required(VERSION 3.11)

project(Babel VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


find_package(Threads REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(SERVER_SRC server/src)
set(CLIENT_SRC client/src)
set(GUI_SRC gui/src)
set(SERVER_INC server/include)
set(CLIENT_INC client/include)
set(GUI_INC gui/include)
set(NETWRK_INC network/)

set(CLIENT_HEADERS
    ${CLIENT_INC}/Client.hpp
    ${GUI_INC}/IUserInterface.hpp
    ${GUI_INC}/QtUserInterface.hpp
    ${GUI_INC}/mainPage.hpp
    ${GUI_INC}/connectionPage.hpp
    ${CLIENT_INC}/ICompressionManager.hpp
    ${CLIENT_INC}/Opus.hpp
    ${CLIENT_INC}/IAudioManager.hpp
    ${CLIENT_INC}/AAudioManager.hpp
    ${CLIENT_INC}/PortAudio.hpp
    ${CLIENT_INC}/QtPtcl.hpp
    ${CLIENT_INC}/INetworkManager.hpp
    ${CLIENT_INC}/ANetworkManager.hpp
    ${CLIENT_INC}/QtNetwork.hpp
    ${CLIENT_INC}/QtUdpNetwork.hpp
    ${NETWRK_INC}/DataPacket.hpp
)


set(CLIENT_SOURCES
    ${NETWRK_INC}/DataPacket.cpp
    ${CLIENT_SRC}/Client.cpp
    ${CLIENT_SRC}/main.cpp
    ${CLIENT_SRC}/Opus.cpp
    ${CLIENT_SRC}/PortAudio.cpp
    ${CLIENT_SRC}/QtNetwork.cpp
    ${CLIENT_SRC}/QtUdpNetwork.cpp
    ${GUI_SRC}/QtUserInterface.cpp
    ${GUI_SRC}/mainPage.cpp
    ${GUI_SRC}/connectionPage.cpp
)

set(SERVER_SOURCES
  ${SERVER_SRC}/Exception.cpp
  ${SERVER_SRC}/Handler.cpp
  ${SERVER_SRC}/main.cpp
  ${SERVER_SRC}/Receiver.cpp
  ${SERVER_SRC}/Server.cpp
  ${SERVER_SRC}/Storage.cpp
  ${SERVER_SRC}/Commands.cpp
)
set(SERVER_HEADERS
  ${SERVER_INC}/ACommands.hpp
  ${SERVER_INC}/AHandler.hpp
  ${SERVER_INC}/AReceiver.hpp
  ${SERVER_INC}/AServer.hpp
  ${SERVER_INC}/AsioPkg.hpp
  ${SERVER_INC}/ClientInfos.hpp
  ${SERVER_INC}/Exception.hpp
  ${SERVER_INC}/Handler.hpp
  ${SERVER_INC}/ICommands.hpp
  ${SERVER_INC}/IHandler.hpp
  ${SERVER_INC}/IReceiver.hpp
  ${SERVER_INC}/IServer.hpp
  ${SERVER_INC}/IStorage.hpp
  ${SERVER_INC}/Receiver.hpp
  ${SERVER_INC}/Server.hpp
  ${SERVER_INC}/Storage.hpp
  ${NETWRK_INC}/INetwork.hpp
  ${NETWRK_INC}/Protocol.hpp
)

include_directories(
    ${SERVER_INC}
    ${GUI_INC}
    ${CLIENT_INC}
    ${NETWRK_INC}
)


if(UNIX)
    SET(CMAKE_CXX_FLAGS)
endif(UNIX)
if (MSVC)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/Debug)
endif ()

add_executable(babel_client ${CLIENT_HEADERS} ${CLIENT_SOURCES} data.qrc)
add_executable(babel_server ${SERVER_HEADERS} ${SERVER_SOURCES})

target_compile_options(babel_client PRIVATE -lrt -lasound -ljack -lpthread -lportaudio)
target_compile_options(babel_server PRIVATE -W -Wall -Wextra)
target_link_libraries(babel_server ${CONAN_LIBS})
target_link_libraries(babel_client PRIVATE Qt5::Core Qt5::Network Qt5::Gui Qt5::Widgets portaudio Threads::Threads opus jack asound dl pthread)

if (MSVC)
    set_target_properties(babel_server
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
	)
endif ()
