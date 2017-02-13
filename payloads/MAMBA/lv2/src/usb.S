#include <lv2/macros.h.S>
#include <lv2/symbols.h>

#ifdef cellUsbdRegisterLdd
LV2_FUNCTION(cellUsbdRegisterLdd, cellUsbdRegisterLdd_symbol)
#endif

#ifdef cellUsbdUnregisterLdd_symbol
LV2_FUNCTION(cellUsbdUnregisterLdd, cellUsbdUnregisterLdd_symbol)
#endif

#ifdef cellUsbdScanStaticDescriptor_symbol
LV2_FUNCTION(cellUsbdScanStaticDescriptor, cellUsbdScanStaticDescriptor_symbol)
#endif

#ifdef cellUsbdOpenPipe_symbol
LV2_FUNCTION(cellUsbdOpenPipe, cellUsbdOpenPipe_symbol)
#endif

#ifdef cellUsbdClosePipe_symbol
LV2_FUNCTION(cellUsbdClosePipe, cellUsbdClosePipe_symbol)
#endif

#ifdef cellUsbdControlTransfer_symbol
LV2_FUNCTION(cellUsbdControlTransfer, cellUsbdControlTransfer_symbol)
#endif

#ifdef cellUsbdBulkTransfer_symbol
LV2_FUNCTION(cellUsbdBulkTransfer, cellUsbdBulkTransfer_symbol)
#endif


