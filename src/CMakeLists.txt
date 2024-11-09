set(Dirs
    "../include"
)

set(SourceFiles
    "main.cpp"
    "DesktopBarnyardWindow.cpp"
)

add_library(src ${SourceFiles})
target_include_directories(src PUBLIC ${Dirs})