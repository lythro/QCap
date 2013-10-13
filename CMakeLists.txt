cmake_minimum_required( VERSION 2.6 )

# add our FindPCAP script
set( CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules )


# find & setup Qt
find_package( Qt4 COMPONENTS QtCore QtNetwork REQUIRED )
add_definitions( ${QT_DEFINITIONS} )

set( QT_WRAP_CPP true )

include( ${QT_USE_FILE} )

# find pcap
find_package( PCAP )

set( sources
	./src/QCap.cpp
	./src/QCapEtherPacket.cpp
)


set( qt_object_header
	./include/QCap.h
)

QT4_WRAP_CPP( moc_header ${qt_object_header} )

include_directories( ${QT_INCLUDES} ${CMAKE_SOURCE_DIR}/include )

# create the library
add_library( qcap SHARED ${sources} ${moc_header} )

# and link againt qt
target_link_libraries( qcap pcap ${QT_LIBRARIES} )



#
# create a test-case
#

add_executable( test ./test/test.cpp )
target_link_libraries( test qcap )
