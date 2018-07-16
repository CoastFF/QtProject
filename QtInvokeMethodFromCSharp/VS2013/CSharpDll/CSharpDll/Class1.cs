using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace CSharpDll
{
    public class CSharpClass
    {
        public CSharpClass() { }

        public int add(int a, int b)
        {
            return a + b;
        }

        public void substract(int a, int b, ref int c)
        {
            c = a- b;
        }

        public static void showBox(string content)
        {
            MessageBox.Show(content, "这是C#的MessageBox",MessageBoxButtons.YesNoCancel);
        }
    }
}
