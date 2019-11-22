#include <iostream>
#include <speechapi_cxx.h>

using namespace Microsoft::CognitiveServices::Speech;

//docs.microsoft.com/en-us/azure/
//cognitive-services/speech-service/quickstarts/speech-to-text-from-microphone
void RecognizeSpeech() {
    auto config = SpeechConfig::FromSubscription("175cc10306674657b22547951918f2e5", "centralus");
    auto recognizer = SpeechRecognizer::FromConfig(config);
    
	std::cout << "Say something...\n";
    auto result = recognizer->RecognizeOnceAsync().get();

    if (result->Reason == ResultReason::RecognizedSpeech) {
        std::cout << "You said: " << result->Text << std::endl;
    } else if (result->Reason == ResultReason::NoMatch) {
        std::cout << "NOMATCH: Speech could not be recognized." << std::endl;
    } else if (result->Reason == ResultReason::Canceled) {
        auto cancellation = CancellationDetails::FromResult(result);
        std::cout << "CANCELED: Reason=" << (int) cancellation->Reason << std::endl;

        if (cancellation->Reason == CancellationReason::Error) {
            std::cout << "CANCELED: ErrorCode= " << (int)cancellation->ErrorCode
                 << std::endl;
            std::cout << "CANCELED: ErrorDetails=" << cancellation->ErrorDetails
                 << std::endl;
            std::cout << "CANCELED: Did you update the subscription info?"
                 << std::endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "");
    RecognizeSpeech();
    return 0;
}
