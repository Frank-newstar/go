#!/usr/bin/python 
# -*- coding: utf-8 -*-
import RPi.GPIO as GPIO

import time
import sys
import Adafruit_GPIO.SPI as SPI
import Adafruit_SSD1306

from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont

# Raspberry Pi pin configuration:
RST = 24
# 128x32 display with hardware I2C:
disp = Adafruit_SSD1306.SSD1306_128_32(rst=RST)

# Initialize library.
disp.begin()

# Clear display.
disp.clear()
disp.display()

# Create blank image for drawing.
# Make sure to create image with mode '1' for 1-bit color.
width = disp.width
height = disp.height
image = Image.new('1', (width, height))

# Get drawing object to draw on image.
draw = ImageDraw.Draw(image)

# Load default font.
#font = ImageFont.load_default()

# Alternatively load a TTF font.  Make sure the .ttf font file is in the same directory as the python script!
# Some other nice fonts to try: http://www.dafont.com/bitmap.php
font = ImageFont.truetype('simfang.ttf', 30)

# First define some constants to allow easy resizing of shapes.
padding = 0
top = padding
bottom = height-padding

# Move left to right keeping track of the current x position for drawing shapes.
# 增加 x 值可以将文字向右移动
x = 0

draw.text((x, top),unicode(sys.argv[1],encoding="utf-8"), font=font, fill=255) # 字段前加 u 表示是文字
disp.image(image)
disp.display()
