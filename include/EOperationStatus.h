#ifndef EOPERATIONSTATUS_H
#define EOPERATIONSTATUS_H

// Enum for operation status (for functions), its easier this way to keep return numbers meaningful
typedef enum EOperationStatus
{
	EOpSuccess = 0, // Operation was successfull
	EOpUnknownError = -1, // Unknown error
} EOperationStatus;

#endif // !EOPERATIONSTATUS_H