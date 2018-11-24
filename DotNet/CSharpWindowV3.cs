using System;
using System.Drawing;
using System.Windows.Forms;

public class CSharpWindowV3:Form
{
	public static void Main()
	{
		Application.Run(new CSharpWindowV3());

	}
	public CSharpWindowV3(){
		Width=800;
		Height=600;
		ResizeRedraw=true;
		
		BackColor=Color.Black;
	
		this.KeyDown+=new KeyEventHandler(MyKeyDown);
		this.MouseDown+=new MouseEventHandler(MyMouseDown);
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
	
	void MyKeyDown(Object sender,KeyEventArgs e){
		MessageBox.Show("Some key is pressed");
	}
	
	void MyMouseDown(Object sender,MouseEventArgs e){
		MessageBox.Show("Mouse key is pressed");
	}
		
}