from libretranslatepy import LibreTranslateAPI

#there is also https://libretranslate.de

lt = LibreTranslateAPI("https://translate.astian.org/")
f = open('languages.json', 'w')
f.write(str(lt.languages()).replace("\'","\""))
f.close()
