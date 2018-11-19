using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace MathLib
{
    [Guid("9A4BA04F-1F9A-4773-A484-665C050418A1")]
    [InterfaceType(ComInterfaceType.InterfaceIsIDispatch)]
    [ComVisible(true)]
    public interface IMath
    {
        [DispId(100)] int[,] AdditionOfInt2DArray(int[,] arr1, int[,] arr2);
        [DispId(101)] int[,] SubstractionOfInt2DArray(int[,] arr1, int[,] arr2);
        [DispId(102)] int[,] MultiplicationOfInt2DArray(int[,] arr1, int[,] arr2);
    }

    [Guid("72FA7FF1-D5A8-435D-AB92-943154E55B09")]
    [ClassInterface(ClassInterfaceType.None)]
    [ComVisible(true)]
    [ProgId("MathLib.Math")]
    public class Math : IMath
    {
        public int[,] AdditionOfInt2DArray(int[,] arr1, int[,] arr2)
        {
            int[,] returnArray = new int[arr1.GetLength(0), arr1.GetLength(1)];

            for (int i = 0; i < arr1.GetLength(0); ++i)
            {
                for (int j = 0; j < arr1.GetLength(1); ++j)
                {
                    returnArray[i, j] = arr1[i, j] + arr2[i, j];
                }
            }
            return returnArray;
        }

        public int[,] SubstractionOfInt2DArray(int[,] arr1, int[,] arr2)
        {
            int[,] returnArray = new int[arr1.GetLength(0), arr1.GetLength(1)];

            for (int i = 0; i < arr1.GetLength(0); ++i)
            {
                for (int j = 0; j < arr1.GetLength(1); ++j)
                {
                    returnArray[i, j] = arr1[i, j] - arr2[i, j];
                }
            }
            return returnArray;
        }

        public int[,] MultiplicationOfInt2DArray(int[,] arr1, int[,] arr2)
        {
            int[,] returnArray = new int[arr1.GetLength(0), arr1.GetLength(1)];
            int temp = 0;

            for (int i = 0; i < arr1.GetLength(0); ++i)
            {
                for (int j = 0; j < arr1.GetLength(1); ++j)
                {
                    temp = 0;
                    for (int k = 0; k < arr1.GetLength(0); ++k)
                    {
                        temp = temp + (arr1[i, k] * arr2[k,j]);
                        
                    }
                    returnArray[i, j] = temp;
                }
               
            }
            return returnArray;
        }
    }
}

// {9A4BA04F-1F9A-4773-A484-665C050418A1}
//{ 0x9a4ba04f, 0x1f9a, 0x4773, { 0xa4, 0x84, 0x66, 0x5c, 0x5, 0x4, 0x18, 0xa1 } };
// {72FA7FF1-D5A8-435D-AB92-943154E55B09}
//{ 0x72fa7ff1, 0xd5a8, 0x435d, { 0xab, 0x92, 0x94, 0x31, 0x54, 0xe5, 0x5b, 0x9 } };
