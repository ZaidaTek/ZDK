/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/

/*
NOTE: Work-in-progress
*/

#include "ZQC.h"

void ZQC_IterateBitShiftR_32(ZT_U32 iInput, void (*iCallback)(void*)) {
	while (0x1) {
		iCallback(&iInput);
		if (!iInput) {return;}
		iInput >>= 1;
	}
}
void ZQC_IterateBitShiftL_32(ZT_U32 iInput, void (*iCallback)(void*)) {
	while (0x1) {
		iCallback(&iInput);
		if (!iInput) {return;}
		iInput <<= 1;
	}
}

int main(int iArgC, char* iArgV[]) {
	void lTest_LSB_MSB(ZT_FLAG iiCandidates[], ZT_INDEX iiLength) {
		void llCallback(void *iiiInput) {printf("0x%08x\t0x%08x\t0x%08x\n", *(ZT_U32*)iiiInput, ZTM_LSB(*(ZT_U32*)iiiInput), ZTM_MSB(*(ZT_U32*)iiiInput));}
		for (int i = 0; i < iiLength; ++i) {
			ZT_U32 llTest = iiCandidates[i];
			printf("i<<=1\tZTM_LSB(i)\tZTM_MSB(i)\n", llTest);
			ZQC_IterateBitShiftL_32(llTest, &llCallback);
			printf("\n");
			printf("i>>=1\tZTM_LSB(i)\tZTM_MSB(i)\n", llTest);
			ZQC_IterateBitShiftR_32(llTest, &llCallback);
			printf("\n");
		}
	}
	ZT_U32 lCandidates[] = {0x1, 0x80000000, 0xffffffff};
	lTest_LSB_MSB(lCandidates, 3);
	return 0;
}
