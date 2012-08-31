
#include "poker.h"
int main(int argc,char ** argv){
    char c,suit;

    string st="--23456789TJQKA";
    while (1){
        vector <char> white_suit,black_suit;
        vector <int> black_card,white_card;
        int count =0;
        while((c=getchar())!='\n'){
            if (c!=' '){
                string str(1,c);
                count++;
                if (count>5){
                    white_card.push_back(int(st.find(str)));
                    suit=getchar();
                    white_suit.push_back(suit);
                }
                else{
                    black_card.push_back(int(st.find(str)));
                    suit=getchar();
                    black_suit.push_back(suit);
                }
            }
        }
         //Now we have both the cards and suits in the vectors

         //get the card counts in the arrays
        int black_kind[14],white_kind[14];//these arrays are used to determine the kind

        reset(black_kind,14);
        reset(white_kind,14);
        card_count(black_kind,black_card);
        card_count(white_kind,white_card);
        sort(black_card.begin(),black_card.end());
        sort(white_card.begin(),white_card.end());
        int black=process(black_kind,black_card,black_suit);
       // cout << "After black " << endl;
        //printarr(black_kind,14);
        int white=process(white_kind,white_card,white_suit);
        //cout << "After WHite " << white << endl;

        if (black > white){
            cout << "black after process" << black << endl;
            cout << "Black wins" << endl;
        }
        else if(black < white){
            cout << "white after process" <<
            white  << endl;
            cout << "White wins" << endl;
        }
        else if(black==white){
            cout << "Black equal" << black<<endl;
            if (black==-1){
                int card=highcard(black_card,white_card);
                if (card==1)
                    cout << "Black wins "<<endl;
                else if (card==2)
                    cout << "White wins "<< endl;
            }
            switch (black){
                case 1:
                    //pair
                    int black_pair;
                    int white_pair;
                    int black_pair_index;
                    int white_pair_index;
                    for (int i=0;i<14;i++){
                        if (black_kind[i]==2){
                            black_pair=black_card[i];
                            black_pair_index=i;
                        }
                        if (white_kind[i]==2){
                            white_pair=white_card[i];
                            white_pair_index=i;
                        }
                    }

                    if(black_pair>white_pair){
                        cout << "Black wins" << endl;
                    }
                    else if(white_pair > black_pair){
                        cout << "White wins" << endl;
                    }
                    else {
                        for (int i=black_pair_index,j=white_pair_index;i<5,j<5;i++,j++){
                            if (black_card[i]>white_card[j]){
                                cout << "Black wins" << endl;
                                break;
                            }
                            else if(black_card[i]< white_card[j]){
                                cout << "White wins" << endl;
                                break;
                            }
                        }
                    }
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5 :
                    break;
                case 6:
                    break;
                case 7:
                    break;
                case 8:
                    break;


            }
        }


    }
    return 0;
}
int process(int kind[14],vector <int> cards,vector <char> suit){
    if (straightFlush(cards,suit)){
        cout << "Straight flush " <<endl;
        printvecint(cards);
        return 8;
    }
    else if(kind4(kind)){
        cout << "4 of a kind"<<endl;
        printarr(kind,14);
        return 7;
    }
    else if (fullhouse(kind)){
        cout << "Full house" << endl;
        printarr(kind,14);
        return 6;
    }
    else if (flush(suit)){
        cout << "Flush" << endl;
        printvec(suit);
        return 5;
    }
    else if (straight(cards)){
        cout << "straight" << endl;
        printvecint(cards);
        return 4;
    }
    else if(kind3(kind)){
        cout << "3 of a kind" << endl;
        printarr(kind,14);
        return 3;
    }
    else if (pair2(kind)){
        cout << "2 pair" << endl;
        printarr(kind,14);
        return 2;
    }
    else if (pair1(kind)){
        cout <<"pair" << endl;
        printarr(kind,14);
        return 1;
    }
    else {
        //means none of the above unlucky hand
        // compare with high card only
        return -1;
    }

}
bool pair1(int kind[14]){
    for (int i=0;i<14;i++){
        if (kind[i]==2){
            return true;
        }
    }
    return false;
}
bool pair2(int kind[14]){
    int count=0;
    for (int i=0;i<14;i++){
        if (kind[i]==2){
            count++;
        }
    }
    if (count == 2){
        return true;
    }
    else {
        return false;
    }
}
bool flush(vector<char> suit){
    if (checkSuit(suit)){
        return true;
    }
    else {
        return false;
    }
}
bool straight(vector<int> cards){
    // the cards are already sorted
    if((cards.back()-cards.front())==5){
        return true;
    }
    else{
        return false;
    }
}
bool fullhouse(int kind[14]){
    //cout << " In Full House" << kind3(kind) << pair1(kind) << endl;
    if (kind3(kind) && pair1(kind)){
      //  cout << "True" << endl;
        return true;
    }
    else {
        return false;
    }
}
bool straightFlush(vector<int> cards,vector<char> suit){
    //the cards are already sorted
    if (checkSuit(suit)&&((cards.back()-cards.front())==5)){
        return true;
    }
    else{
            return false;
    }
}
bool kind4(int kind[14]){
    for(int i=0;i<14 ;i++){
        if(kind[i]==4){
            return true;
        }
    }
    return false;
}
bool kind3(int kind[14]){
    for(int i=0;i<14;i++){
        if (kind[i]==3){
            return true;
        }
    }
    return false;
}
bool checkSuit(vector <char> suit){
    char su=suit[0];
    for (int i=0;i<suit.size();i++){
        if (suit[i]!=su){
            return false;
        }
    }
    return true;
}
void card_count(int  kind[14],vector <int> card){
    for (int i=0;i<card.size();i++){
            if (kind[card[i]]!=0){
                kind[card[i]]++;
            }
            else{
                kind[card[i]]=1;
            }
        }

}

void printvec(vector <char> vec){
    for (int i=0;i<vec.size();i++){
        cout << vec[i];
    }
    cout << endl;

}
void printvecint(vector <int> vec){
    for (int i=0;i<vec.size();i++){
        cout << vec[i];
    }
    cout << endl;

}

void printarr(int arr[],int size){
    for (int i=0;i<size;i++){
        cout << arr[i] ;
    }
    cout << endl;

}
void reset(int arr[],int size){
    for (int i=0;i<size;i++){
        arr[i]=0;
    }

}
int highcard(vector <int>black,vector <int> white){
    //returns the hights card after all comparisions
    reverse(black.begin(),black.end());
    reverse(white.begin(),white.end());
    printvecint(black);
    printvecint(white);
    for (int i=0;i<black.size();i++){
        if (black[i]==white[i]){
            continue;
        }
        else if (black[i]>white[i]){
            return 1;
        }
        else if(black[i]<white[i]){
            return 2;
        }

    }
}
