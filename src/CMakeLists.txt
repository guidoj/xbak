add_library(base STATIC
            basicfile.cc
            event.cc
            exception.cc
            filebuffer.cc
            geometry.cc
            subject.cc
            vertex.cc)

add_library(game STATIC
            camera.cc
            chapter.cc
            configresource.cc
            game.cc
            gameresource.cc
            genericobject.cc
            inventory.cc
            inventoryitem.cc
            orientation.cc
            party.cc
            patternpolygonobject.cc
            playercharacter.cc
            polygonobject.cc
            position.cc
            preferences.cc
            preferencesdialogbridge.cc
            scene.cc
            scenefactory.cc
            solidpolygonobject.cc
            spriteobject.cc
            statistics.cc
            zone.cc)

add_library(guitoolkit STATIC
            badgewidget.cc
            buttonwidget.cc
            characterbuttonwidget.cc
            choicewidget.cc
            combatviewwidget.cc
            compasswidget.cc
            containerwidget.cc
            dialog.cc
            dialogfactory.cc
            dialogwindow.cc
            equipmentitemwidget.cc
            equipmentwidget.cc
            font.cc
            gameviewwidget.cc
            hotspotwidget.cc
            image.cc
            imagebuttonwidget.cc
            imagewidget.cc
            inventoryitemwidget.cc
            inventorywidget.cc
            mapviewwidget.cc
            movieplayer.cc
            palette.cc
            panelwidget.cc
            pointer.cc
            pointermanager.cc
            popupwidget.cc
            portraitwidget.cc
            ratingswidget.cc
            skilllevelwidget.cc
            skillswidget.cc
            sound.cc
            text.cc
            textbuttonwidget.cc
            textwidget.cc
            widget.cc
            widgetfactory.cc
            worldviewwidget.cc)

add_library(resource STATIC
            animationresource.cc
            bookresource.cc
            configfile.cc
            dialogresource.cc
            directories.cc
            filemanager.cc
            fontresource.cc
            gamefile.cc
            imageresource.cc
            labelresource.cc
            movieresource.cc
            nameresource.cc
            objectresource.cc
            paletteresource.cc
            partyresource.cc
            rampresource.cc
            requestresource.cc
            resourcearchive.cc
            resourcefile.cc
            resourceindex.cc
            resourcetag.cc
            screenresource.cc
            soundresource.cc
            tableresource.cc
            taggedimageresource.cc
            taggedresource.cc
            tiledataresource.cc
            tileworldresource.cc)

add_library(driver STATIC
            mediatoolkit.cc
            sdl_audio.cc
            sdl_clock.cc
            sdl_toolkit.cc
            sdl_video.cc
            video.cc)

add_executable(xbak
               xbak.cc
               gameapplication.cc
               gamestate.cc)
target_link_libraries(xbak
                      game
                      guitoolkit
                      resource
                      driver
                      base
                      SDL2_mixer::SDL2_mixer
                      ${SDL2_LIBRARIES}                      )

add_executable(convertresource
               convertresource.cc
               bmp.cc)
target_link_libraries(convertresource
                      guitoolkit
                      resource
                      driver
                      base
                      SDL2_mixer::SDL2_mixer
                      ${SDL2_LIBRARIES})

add_executable(dumpads
               dumpads.cc)
target_link_libraries(dumpads
                      resource
                      base
                      ${SDL2_LIBRARIES})

add_executable(dumpbmx
               dumpbmx.cc)
target_link_libraries(dumpbmx
                      guitoolkit
                      resource
                      driver
                      base
                      SDL2_mixer::SDL2_mixer
                      ${SDL2_LIBRARIES})

add_executable(dumpbok
               dumpbok.cc)
target_link_libraries(dumpbok
                      resource
                      base
                      ${SDL2_LIBRARIES})

add_executable(dumpddx
               dumpddx.cc)
target_link_libraries(dumpddx
                      resource
                      base
                      ${SDL2_LIBRARIES})

add_executable(dumpfnt
               dumpfnt.cc)
target_link_libraries(dumpfnt
                      guitoolkit
                      resource
                      driver
                      base
                      SDL2_mixer::SDL2_mixer
                      ${SDL2_LIBRARIES})

add_executable(dumpgam
               dumpgam.cc)
target_link_libraries(dumpgam
                      game
                      guitoolkit
                      resource
                      driver
                      base
                      SDL2_mixer::SDL2_mixer
                      ${SDL2_LIBRARIES})

add_executable(dumplbl
               dumplbl.cc)
target_link_libraries(dumplbl
                      resource
                      base
                      ${SDL2_LIBRARIES})

add_executable(dumpobj
               dumpobj.cc)
target_link_libraries(dumpobj
                      resource
                      base
                      ${SDL2_LIBRARIES})

add_executable(dumppal
               dumppal.cc)
target_link_libraries(dumppal
                      guitoolkit
                      resource
                      driver
                      base
                      SDL2_mixer::SDL2_mixer
                      ${SDL2_LIBRARIES})

add_executable(dumpreq
               dumpreq.cc)
target_link_libraries(dumpreq
                      resource
                      base
                      ${SDL2_LIBRARIES})

add_executable(dumpscx
               dumpscx.cc)
target_link_libraries(dumpscx
                      guitoolkit
                      resource
                      driver
                      base
                      SDL2_mixer::SDL2_mixer
                      ${SDL2_LIBRARIES})

add_executable(dumpsnd
               dumpsnd.cc)
target_link_libraries(dumpsnd
                      guitoolkit
                      resource
                      driver
                      base
                      SDL2_mixer::SDL2_mixer
                      ${SDL2_LIBRARIES})

add_executable(dumptbl
               dumptbl.cc)
target_link_libraries(dumptbl
                      resource
                      base
                      ${SDL2_LIBRARIES})

add_executable(dumpttm
               dumpttm.cc)
target_link_libraries(dumpttm
                      resource
                      base
                      ${SDL2_LIBRARIES})

add_executable(dumpwld
               dumpwld.cc)
target_link_libraries(dumpwld
                      resource
                      base
                      ${SDL2_LIBRARIES})

add_executable(resourcedemo
               resourcedemo.cc
               testapplication.cc)
target_link_libraries(resourcedemo
                      guitoolkit
                      resource
                      driver
                      base
                      SDL2_mixer::SDL2_mixer
                      ${SDL2_LIBRARIES})
