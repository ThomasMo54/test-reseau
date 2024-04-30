# Recherche la bibliothèque SDL2_net
# Cette module recherche la bibliothèque SDL2_net et définit les variables
# SDL2_NET_FOUND - vrai si la bibliothèque SDL2_net est trouvée
# SDL2_NET_INCLUDE_DIRS - les répertoires d'en-tête pour SDL2_net
# SDL2_NET_LIBRARIES - les bibliothèques à lier pour SDL2_net
#
# Une fois cela inclus, vous pouvez utiliser
#    find_package(SDL2_net REQUIRED)
# pour trouver la bibliothèque SDL2_net.
#

# Le répertoire contenant le fichier SDL2_net.h
# Cela peut être défini avec la variable d'environnement SDL2_NET_DIR.
if (NOT SDL2_NET_INCLUDE_DIRS)
    if (DEFINED ENV{SDL2_NET_DIR})
        list(APPEND CMAKE_PREFIX_PATH "/usr/include/SDL2")
    endif ()
    find_path(SDL2_NET_INCLUDE_DIRS SDL2/SDL_net.h)
endif ()

# Les bibliothèques à lier
# Cela peut être défini avec la variable d'environnement SDL2_NET_LIBRARY.
if (NOT SDL2_NET_LIBRARIES)
    if (DEFINED ENV{SDL2_NET_LIBRARY})
        list(APPEND CMAKE_LIBRARY_PATH "/usr/lib/x86_64-linux-gnu")
    endif ()
    find_library(SDL2_NET_LIBRARIES NAMES SDL2_net)
endif ()

# Le résultat
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL2_net DEFAULT_MSG SDL2_NET_LIBRARIES SDL2_NET_INCLUDE_DIRS)
