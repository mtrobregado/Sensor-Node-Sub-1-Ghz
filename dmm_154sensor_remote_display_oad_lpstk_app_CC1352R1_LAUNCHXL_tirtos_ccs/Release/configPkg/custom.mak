## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,em4f linker.cmd package/cfg/ble_oad_lpstk_release_pem4f.oem4f

# To simplify configuro usage in makefiles:
#     o create a generic linker command file name 
#     o set modification times of compiler.opt* files to be greater than
#       or equal to the generated config header
#
linker.cmd: package/cfg/ble_oad_lpstk_release_pem4f.xdl
	$(SED) 's"^\"\(package/cfg/ble_oad_lpstk_release_pem4fcfg.cmd\)\"$""\"C:/ti/ccsv103workspace/CC1352Rv510/dmm_154sensor_remote_display_oad_lpstk_app_CC1352R1_LAUNCHXL_tirtos_ccs/Release/configPkg/\1\""' package/cfg/ble_oad_lpstk_release_pem4f.xdl > $@
	-$(SETDATE) -r:max package/cfg/ble_oad_lpstk_release_pem4f.h compiler.opt compiler.opt.defs
