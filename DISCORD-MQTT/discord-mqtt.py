# Copyright (c) 2022 Esteban Cadic
# This code is licensed under MIT license (see LICENSE file for details)

import configparser
import paho.mqtt.client as mqtt
import urllib.parse
import discord
from discord.ext import commands

# Config
config = configparser.ConfigParser()
config.read('config.ini')


# MQTT
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker!")
    else:
        raise Exception("Failed to connect, return code {}".format(rc))


client = mqtt.Client(config['mqtt']['client_id'])
client.username_pw_set(config['mqtt']['user'], config['mqtt']['password'])
client.on_connect = on_connect
client.connect(config['mqtt']['ip'])
client.loop_start()


# Discord
intents = discord.Intents.default()
intents.message_content = True
bot = commands.Bot(command_prefix='.', intents=intents)

@bot.command()
async def write(ctx, *, arg):
    try:
        # The screen can only handle Windows-1252 encoding
        arg.encode('cp1252')
    except UnicodeEncodeError:
        await ctx.reply("Y'a des caractères que je ne peux pas afficher dans ton message...")
        raise

    if len(arg) > 40:
        await ctx.reply("Ton message est trop long :exploding_head:")
        raise Exception("Message too long: {}".format(arg))

    print("Publication of the following message: {}".format(arg))
    client.publish(config['mqtt']['channel'],
                   urllib.parse.quote(arg, encoding='cp1252'))
    await ctx.message.add_reaction('\u2705')
    # Special characters are encoded with the % followed by the location of the character in the 1252 table

bot.run(config['discord']['token'])
