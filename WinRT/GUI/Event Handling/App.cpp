#include "pch.h"
#include "App.h"
#include "MyPage.h"

using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Platform;

void MyCallBackMethod(Windows::UI::Xaml::ApplicationInitializationCallbackParams^ params) {
	App^ app = ref new App();
}

int main(Array<String^>^ args) {
	ApplicationInitializationCallback^ callback = ref new ApplicationInitializationCallback(MyCallBackMethod);
	Application::Start(callback);
	return 0;
}

void App::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ args) {
	Page^ myPage = ref new MyPage();
	
	Window::Current->Content = myPage;
	Window::Current->Activate();
}
