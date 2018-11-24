using System;
using System.Drawing;
using System.Windows.Forms;

public class CSharpWindowV1:Form
{
	public static void Main()
	{
		Application.Run(new CSharpWindowV1());

	}
	public CSharpWindowV1(){
		Width=800;
		Height=600;
		ResizeRedraw=true;
	}
}