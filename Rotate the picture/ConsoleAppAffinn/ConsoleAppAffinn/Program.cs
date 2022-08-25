using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.IO;

using System.Runtime.InteropServices;

namespace ConsoleAppKernel3
{

    class Program
    {
              
        static void Main(string[] args)
        {
            Console.WriteLine("Аффинные преобразования!");

            using (FileStream bmpStream = new FileStream(args[0], FileMode.Open, FileAccess.Read))
            using (Bitmap image = new System.Drawing.Bitmap(bmpStream))
            {
                Apply(image);
            }
            Console.ReadKey();
        }

        public static byte[] MyLoadBMP(Bitmap input)
        {
            BitmapData curBitmapData = input.LockBits(new Rectangle(0, 0, input.Width, input.Height), ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            int stride = curBitmapData.Stride;
            byte[] data = new byte[stride * input.Height];
            Marshal.Copy(curBitmapData.Scan0, data, 0, data.Length);
            input.UnlockBits(curBitmapData);

            byte[] outdata = new byte[input.Width * 3 * input.Height];

            for (int i = 0; i < input.Height; i++)
            {
                for (int j = 0; j < input.Width; j++)
                {
                    outdata[j * 3 + 0 + i * 3 * input.Width] = data[i * stride + j * 3 + 0];
                    outdata[j * 3 + 1 + i * 3 * input.Width] = data[i * stride + j * 3 + 1];
                    outdata[j * 3 + 2 + i * 3 * input.Width] = data[i * stride + j * 3 + 2];
                }
            }

            Console.WriteLine("Исходное изображение: ширина {0}, высота {1}", input.Width, input.Height);

            return outdata;
        }

        public static void Apply(Bitmap input)
        {
            byte[] inputBytes = MyLoadBMP(input);
            byte[] outputBytes = new byte[inputBytes.Length];

            int width = input.Width;
            int height = input.Height;
            
            float sX = (float)0.5;  // масштабный коэффицент по оси X
            float sY = (float)0.7;  // масштабный коэффицент по оси Y
            float ang = (float)45;  // угол поворота
            float tX = (float)width - 1;    // X-координата вектора переноса
            float tY = (float)-1;            // Y-координата вектора переноса

            for (int x = 0; x < width; x++)
            {
                for (int y = 0; y < height; y++)
                {
                    Matrix myMatrix = new Matrix();
                    myMatrix.Scale(sX, sY, MatrixOrder.Append);
                    myMatrix.Rotate(ang);
                    myMatrix.Translate(tX, tY, MatrixOrder.Append);

                    Point[] pnt = { new Point(x, y) };

                    myMatrix.TransformPoints(pnt);
                    //
                    int pixelPosX = pnt[0].X;
                    int pixelPosY = pnt[0].Y;
                    if ((pixelPosX < 0) || (pixelPosX >= width) || (pixelPosY < 0) || (pixelPosY >= height))
                        continue;

                    byte r = inputBytes[3 * (width * y + x) + 0];
                    byte g = inputBytes[3 * (width * y + x) + 1];
                    byte b = inputBytes[3 * (width * y + x) + 2];


                    //Записываем значения в результирующее изображение
                    //
                    for (int ii = 0; ii < Math.Ceiling(sX); ii++)
                    {
                        for (int jj = 0; jj < Math.Ceiling(sY); jj++)
                        {
                            if (pixelPosY + jj < height && pixelPosX + ii < width)
                            {
                                outputBytes[3 * (width * (pixelPosY + jj) + (pixelPosX + ii)) + 0] = (byte)r;
                                outputBytes[3 * (width * (pixelPosY + jj) + (pixelPosX + ii)) + 1] = (byte)g;
                                outputBytes[3 * (width * (pixelPosY + jj) + (pixelPosX + ii)) + 2] = (byte)b;
                            }
                        }
                    }
                    //
                    //outputBytes[3 * (width * pixelPosY + pixelPosX) + 0] = (byte)r;
                    //outputBytes[3 * (width * pixelPosY + pixelPosX) + 1] = (byte)g;
                    //outputBytes[3 * (width * pixelPosY + pixelPosX) + 2] = (byte)b;
                }
            }

            MySaveBMP(outputBytes, (int)(width), (int)(height));

            return;
        }

        private static void MySaveBMP(byte[] buffer, int width, int height)
        {
            Bitmap b = new Bitmap(width, height, PixelFormat.Format24bppRgb);

            Rectangle BoundsRect = new Rectangle(0, 0, width, height);
            BitmapData bmpData = b.LockBits(BoundsRect,
                                            ImageLockMode.WriteOnly,
                                            b.PixelFormat);

            IntPtr ptr = bmpData.Scan0;

            // add back dummy bytes between lines, make each line be a multiple of 4 bytes
            int skipByte = bmpData.Stride - width * 3;
            byte[] newBuff = new byte[buffer.Length + skipByte * height];
            for (int j = 0; j < height; j++)
            {
                Buffer.BlockCopy(buffer, j * width * 3, newBuff, j * (width * 3 + skipByte), width * 3);
            }

            // fill in rgbValues
            Marshal.Copy(newBuff, 0, ptr, newBuff.Length);
            b.UnlockBits(bmpData);
            b.Save(@"C:\Users\Yablonovsky\Downloads\ConsoleAppAffinn\ConsoleAppAffinn\PicOut2.bmp", ImageFormat.Bmp);
        }
    }
}
