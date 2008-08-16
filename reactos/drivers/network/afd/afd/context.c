/* $Id$
 * COPYRIGHT:        See COPYING in the top level directory
 * PROJECT:          ReactOS kernel
 * FILE:             drivers/net/afd/afd/context.c
 * PURPOSE:          Ancillary functions driver
 * PROGRAMMER:       Art Yerkes (ayerkes@speakeasy.net)
 * UPDATE HISTORY:
 * 20040708 Created
 */
#include "afd.h"
#include "tdi_proto.h"
#include "tdiconn.h"
#include "debug.h"

NTSTATUS STDCALL
AfdGetContext( PDEVICE_OBJECT DeviceObject, PIRP Irp,
	       PIO_STACK_LOCATION IrpSp ) {
    NTSTATUS Status = STATUS_INVALID_PARAMETER;
    PFILE_OBJECT FileObject = IrpSp->FileObject;
    PAFD_FCB FCB = FileObject->FsContext;
    UINT ContextSize = IrpSp->Parameters.DeviceIoControl.OutputBufferLength;

    if( !SocketAcquireStateLock( FCB ) ) return LostSocket( Irp );

    if( FCB->ContextSize < ContextSize ) ContextSize = FCB->ContextSize;

    if( FCB->Context ) {
	RtlCopyMemory( Irp->UserBuffer,
		       FCB->Context,
		       ContextSize );
	Status = STATUS_SUCCESS;
    }

    AFD_DbgPrint(MID_TRACE,("Returning %x\n", Status));

    return UnlockAndMaybeComplete( FCB, Status, Irp, 0, NULL );
}

NTSTATUS STDCALL
AfdSetContext( PDEVICE_OBJECT DeviceObject, PIRP Irp,
	       PIO_STACK_LOCATION IrpSp ) {
    NTSTATUS Status = STATUS_BUFFER_TOO_SMALL;
    PFILE_OBJECT FileObject = IrpSp->FileObject;
    PAFD_FCB FCB = FileObject->FsContext;

    if( !SocketAcquireStateLock( FCB ) ) return LostSocket( Irp );

    if( FCB->Context ) {
	ExFreePool( FCB->Context );
	FCB->Context = NULL;
    }

    if( FCB->ContextSize <
	IrpSp->Parameters.DeviceIoControl.InputBufferLength ) {
	FCB->Context =
	    ExAllocatePool
	    ( PagedPool,
	      IrpSp->Parameters.DeviceIoControl.InputBufferLength );

	if( !FCB->Context ) return UnlockAndMaybeComplete( FCB, STATUS_NO_MEMORY, Irp, 0, NULL );

	RtlCopyMemory( FCB->Context,
		       IrpSp->Parameters.DeviceIoControl.Type3InputBuffer,
		       IrpSp->Parameters.DeviceIoControl.InputBufferLength );
	Status = STATUS_SUCCESS;
    }

    AFD_DbgPrint(MID_TRACE,("Returning %x\n", Status));

    return UnlockAndMaybeComplete( FCB, Status, Irp, 0, NULL );
}
