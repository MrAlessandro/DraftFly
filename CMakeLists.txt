cmake_minimum_required(VERSION 3.20)

project(DraftFly)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-ld_classic")

# Imposta la cartella di output per i file compilati
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Aggiungi la sottodirectory "src" per compilare il codice sorgente
# add_subdirectory(src)

# Specifica l'output come una libreria condivisa
add_library(DraftFly SHARED)

# Aggiungi i file sorgente al target della libreria
target_sources(DraftFly PRIVATE src/sender.cpp src/receiver.cpp)

# Specifica le directory include per il progetto
target_include_directories(DraftFly PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Aggiungi un eseguibile di test
add_executable(test_draftfly_receiver tests/test_draftfly_receiver.cpp)
add_executable(test_draftfly_sender tests/test_draftfly_sender.cpp)

target_include_directories(test_draftfly_receiver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(test_draftfly_sender PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Collega la libreria al test
target_link_libraries(test_draftfly_receiver DraftFly)
target_link_libraries(test_draftfly_sender DraftFly)

# Aggiungi il test per eseguire la funzione "printDebugMessage"
add_test(NAME RunReceiver COMMAND test_draftfly_receiver)
add_test(NAME RunSender COMMAND test_draftfly_sender)
