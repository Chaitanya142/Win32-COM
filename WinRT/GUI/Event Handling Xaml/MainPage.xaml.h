//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Platform;

#include "MainPage.g.h"

namespace HelloWorld
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

		void OnKeyDown(CoreWindow^ sender, KeyEventArgs^ args);

		void OnButtonClick(Object^ sender, RoutedEventArgs^ args);

	};
}
