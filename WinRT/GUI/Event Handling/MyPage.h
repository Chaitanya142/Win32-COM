#pragma once
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Platform;

ref class MyPage sealed :Page {
private:
	TextBlock^ textBlock;
	
public:
	MyPage();

	void OnKeyDown(CoreWindow^ sender, KeyEventArgs^ args);

	void OnButtonClick(Object^ sender, RoutedEventArgs^ args);
};
