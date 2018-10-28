Imports System.Windows.Forms
Imports AutomationServerTypeLibForDotNet

Public Class VBAutomation
	Inherits Form
	Public Sub New()
		Dim MyIDispatch As Object
		Dim MyRef As New CMyMathClass
		MyIDispatch=MyRef
		Dim iNum1=175
		Dim iNum2=125
		Dim iSum=MyIDispatch.SumOfTwoIntegers(iNum1,iNum2)
		Dim str As String=String.Format("Sum of {0} and {1} is {2}",iNum1,iNum2,iSum)
		MsgBox(str)
		Dim iSub=MyIDispatch.SubstractionOfTwoIntegers(iNum1,iNum2)
		str =String.Format("Sub of {0} and {1} is {2}",iNum1,iNum2,iSub)
		MsgBox(str)
		End
	End Sub
		
	<STAThread()>
	Shared Sub Main()
		Application.EnableVisualStyles()
		Application.Run(New VBAutomation())
	END Sub
End Class

