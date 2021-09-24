from libretranslatepy import LibreTranslateAPI
import io
import argparse

parser = argparse.ArgumentParser(description='Translate')
parser.add_argument("txt_translate", help="The text to translate.")
parser.add_argument("src_lang_code", help="The source language code.")
parser.add_argument("trg_lang_code", help="The target language code.")
args = parser.parse_args()

# there is also https://libretranslate.de
# need python3.8+
# pip install libretranslatepy
# https://github.com/argosopentech/LibreTranslate-py

lt = LibreTranslateAPI("https://translate.astian.org/")
f = io.open('res.txt', 'w', encoding="utf-8")
f.write(lt.translate(args.txt_translate, args.src_lang_code, args.trg_lang_code))
f.close()


