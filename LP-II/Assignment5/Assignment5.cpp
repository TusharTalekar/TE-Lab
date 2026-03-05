#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

class chatbot{
    vector<string> greetingKeywords;
    vector<string> balanceKeywords;
    vector<string> loanKeywords;
    vector<string> cardKeywords;
    vector<string> hoursKeywords;
    public:
    chatbot(){
        greetingKeywords={"hey","hi","hello"};
        balanceKeywords={"balance","check balance","account balance"};
        loanKeywords={"loan","borrow","interest"};
        cardKeywords={"card","credit card","debit card","card issue","lost card","stolen card","lost","stolen"};
        hoursKeywords={"hours","open","closing","time","working"};
    }

    bool containsGreet(const string &str){
        for (const string& word : greetingKeywords) 
            if (str.find(word) != string::npos) 
                return true;
        return false;
    }
    bool containsBalanceInquiry(const string &str){
        for (const string& word : balanceKeywords) 
            if (str.find(word) != string::npos) 
                return true;
        return false;
    }
    bool containsLoanInquiry(const string &str){
        for (const string& word : loanKeywords) 
            if (str.find(word) != string::npos) 
                return true;
        return false;
    }
    bool containsCardInquiry(const string &str){
        for (const string& word : cardKeywords) 
            if (str.find(word) != string::npos) 
                return true;
        return false;
    }
    bool containsTimeInquiry(const string &str){
        for (const string& word : hoursKeywords) 
            if (str.find(word) != string::npos) 
                return true;
        return false;
    }

    void bankingChatbot(){
        cout << "Welcome to SecureBank Customer Support!" << endl;
        cout << "Type 'exit' to end the chat.\n" << endl;
        string user_input;
        while(true){
            cout << "You: ";
            getline(cin, user_input);
            transform(user_input.begin(), user_input.end(), user_input.begin(), ::tolower);
            if(user_input=="exit"){
                cout << "Bot: Thank you for banking with us. Goodbye!" << endl;
                break;
            }else if(containsGreet(user_input)){
                cout << "Bot: Hello! How can I assist you today?" << endl;
            }else if(containsBalanceInquiry(user_input)){
                cout << "Bot: Please enter your account number to check your balance." << endl;
            }else if(containsLoanInquiry(user_input)){
                cout << "Bot: We offer personal, home, and auto loans. Would you like details on any specific loan?" << endl;
            }else if(containsCardInquiry(user_input)){
                cout << "Bot: If your card is lost or stolen, please call our emergency line immediately or type 'block card'"<<endl;
            }else if(containsTimeInquiry(user_input)){
                cout << "Bot: Our branches are open Monday to Friday from 9 AM to 5 PM." << endl;
            }else{
                cout << "Bot: I'm sorry, I didn't understand that. Could you please rephrase?" << endl;
            }
        };
    }
};

int main(){
    chatbot c;
    c.bankingChatbot();

    return 0;

}