/*
 * Copyright (c) 2020 Piotr Stolarz
 * OneWireNg: Ardiono 1-wire service library
 *
 * Distributed under the 2-clause BSD License (the License)
 * see accompanying file LICENSE for details.
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more information.
 */

/**
 * 1-wire overdrive mode example. Requires @c CONFIG_OVERDRIVE_ENABLED.
 */
#include "OneWireNg_CurrentPlatform.h"

#define OW_PIN          10

static OneWireNg *ow = NULL;

static void printId(const OneWireNg::Id& id)
{
    Serial.print(id[0], HEX);
    for (size_t i=1; i < sizeof(OneWireNg::Id); i++) {
        Serial.print(':');
        Serial.print(id[i], HEX);
    }
    Serial.println();
}

void setup()
{
    OneWireNg::Id id;
    OneWireNg::ErrorCode ec;

    ow = new OneWireNg_CurrentPlatform(OW_PIN, false);
    delay(500);

    Serial.begin(115200);

    /* enable overdrive (OD) mode on all devices supporting it */
    ow->overdriveAll();

    /* all subsequent communication in OD mode */

    /* search for OD enabled devices */
    Serial.println("Overdrive enabled devices:");
    do
    {
        ec = ow->search(id);
        if (!(ec == OneWireNg::EC_MORE || ec == OneWireNg::EC_DONE))
            break;

        printId(id);
    } while (ec == OneWireNg::EC_MORE);

    /* back to standard mode */
    ow->setOverdrive(false);
}

void loop()
{
}
