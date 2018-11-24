using System;
using System.Drawing;
using System.Windows.Forms;

public class CSharpWindowV2:Form
{
	public static void Main()
	{
		Application.Run(new CSharpWindowV2());

	}
	public CSharpWindowV2(){
		Width=800;
		Height=600;
		ResizeRedraw=true;
		
		BackColor=Color.Black;
	}
	
	protected override void OnPaint(PaintEventArgs pea){
	Graphics grfx =pea.Graphics;
	StringFormat strfmt=new StringFormat();
	
	strfmt.Alignment=StringAlignment.Center;
	strfmt.LineAlignment=StringAlignment.Center;
	
	grfx.DrawString("Hello World!!!",
					Font,
					new SolidBrush(System.Drawing.Color.Green),
					ClientRectangle,
					strfmt);

	}
}