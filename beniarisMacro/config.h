/*
Copyright 2025 Your Name

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// Encoder button (if using separate button pin)
#define ENCODER_BUTTON_PIN F6

// Debounce reduces chatter (unintended double-presses)
#define DEBOUNCE 5

/* OLED Display Configuration */
#define OLED_DISPLAY_128X64
#define OLED_TIMEOUT 30000

// Add these pin definitions:
#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN D0
#define I2C1_SDA_PIN D1
