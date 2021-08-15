# invoke SourceDir generated makefile for ble_oad_lpstk_release.pem4f
ble_oad_lpstk_release.pem4f: .libraries,ble_oad_lpstk_release.pem4f
.libraries,ble_oad_lpstk_release.pem4f: package/cfg/ble_oad_lpstk_release_pem4f.xdl
	$(MAKE) -f C:\ti\ccsv103workspace\CC1352Rv510\dmm_154sensor_remote_display_oad_lpstk_app_CC1352R1_LAUNCHXL_tirtos_ccs/src/makefile.libs

clean::
	$(MAKE) -f C:\ti\ccsv103workspace\CC1352Rv510\dmm_154sensor_remote_display_oad_lpstk_app_CC1352R1_LAUNCHXL_tirtos_ccs/src/makefile.libs clean

