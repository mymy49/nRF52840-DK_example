#!/bin/bash

# Update types.h
sed -i 's/struct llData_t/typedef struct/g' yss/inc/bluetooth/types.h
sed -i 's/accessAddress;/access_address;/g' yss/inc/bluetooth/types.h
sed -i 's/crcInit\[/crc_init\[/g' yss/inc/bluetooth/types.h
sed -i 's/windowSize;/window_size;/g' yss/inc/bluetooth/types.h
sed -i 's/windowOffset;/window_offset;/g' yss/inc/bluetooth/types.h
sed -i 's/channelMap\[/channel_map\[/g' yss/inc/bluetooth/types.h
sed -i 's/hopAndSca;/hop_and_sca;/g' yss/inc/bluetooth/types.h
sed -i 's/};/} ble_ll_conn_req_data_t;/g' yss/inc/bluetooth/types.h

# Update Ble4p0.h
sed -i 's/llData_t/ble_ll_conn_req_data_t/g' yss/inc/bluetooth/Ble4p0.h

# Update bluetooth_Ble4p0.cpp
sed -i 's/llData_t/ble_ll_conn_req_data_t/g' yss/src/bluetooth/bluetooth_Ble4p0.cpp
sed -i 's/mLinkLayerData.accessAddress/mLinkLayerData.access_address/g' yss/src/bluetooth/bluetooth_Ble4p0.cpp
sed -i 's/mLinkLayerData.crcInit/mLinkLayerData.crc_init/g' yss/src/bluetooth/bluetooth_Ble4p0.cpp
sed -i 's/mLinkLayerData.windowSize/mLinkLayerData.window_size/g' yss/src/bluetooth/bluetooth_Ble4p0.cpp
sed -i 's/mLinkLayerData.windowOffset/mLinkLayerData.window_offset/g' yss/src/bluetooth/bluetooth_Ble4p0.cpp
sed -i 's/mLinkLayerData.channelMap/mLinkLayerData.channel_map/g' yss/src/bluetooth/bluetooth_Ble4p0.cpp
sed -i 's/mLinkLayerData.hopAndSca/mLinkLayerData.hop_and_sca/g' yss/src/bluetooth/bluetooth_Ble4p0.cpp

