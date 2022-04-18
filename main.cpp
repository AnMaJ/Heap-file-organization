//
//  main.cpp
//  Heaps_dbms
//
//  Created by Mansi on 16/04/22.
//

#include <bits/stdc++.h>
#include<vector>
using namespace std;


/*...............................................................*/
class page{
    
    public:
    page *prev_page, *next_page;
    int num_records,free_space_address,pid,space_left;
    vector<int> records;
    vector<int> book_keeping;
    
    int page_search(int n);
    bool page_insert(int rec_size,int n);
    
    
    page(int pgid,page *prev,int page_size){
        pid=pgid;
        free_space_address=0;
        next_page=NULL;
        space_left=page_size-16;
        num_records=0;
        prev_page=prev;
    }
    
};

bool page::page_insert(int rec_size,int n){
    if(space_left<(rec_size+4)){
        return false;
    }
    records.push_back(n);
    book_keeping.push_back(rec_size);
    num_records++;
    free_space_address+=rec_size;
    space_left-=(rec_size+4);
    return true;
}


int page::page_search(int n){
    for(int i=0;i<num_records;i++){
        if(records[i]==n){
            return i;
        }
    }
    return -1;
}
/*...............................................................*/

class heap{
    int pagesize;
    page* head;
    public:
    heap(int page_size){
        pagesize=page_size;
        head=NULL;
        num_pages=0;
    }
    int num_pages;
    bool search(int n);
    void display();
    bool insert(int rec_size,int n);
};
bool heap::insert(int rec_size,int n){
    page* curr_page=head,*lastpg=NULL;
    while(curr_page!=NULL){
        lastpg=curr_page;
        if((curr_page->space_left)>=(rec_size+4)){
            return curr_page->page_insert(rec_size,n);
        }
        curr_page=curr_page->next_page;
    }
    if(head==NULL){
        page* newpage=new page(0,NULL,pagesize);
        num_pages++;
        head=newpage;
        return newpage->page_insert(rec_size,n);
    }
    else{
        page * newpage=new page((lastpg->pid)+1,lastpg,pagesize);
        lastpg->next_page=newpage;
        num_pages++;
        return newpage->page_insert(rec_size,n);
    }
}

bool heap::search(int n){
    page* curr_page=head;
    while(curr_page!=NULL){
        int slot=curr_page->page_search(n);
        if(slot!=-1){
            cout<<curr_page->pid<<" "<<slot<<endl;
            return true;
        }
        curr_page=curr_page->next_page;
    }
    cout<<-1<<" "<<-1<<endl;
    return false;
}


void heap::display(){
    cout<<num_pages<<" ";
    page* curr_page=head;
    while(curr_page!=NULL){
        cout<<(curr_page->num_records)<<" ";
        curr_page=curr_page->next_page;
    }
    cout<<endl;
}

/*...............................................................*/

int main(){
    int page_size,code;
    cin>>page_size>>code;
    heap h(page_size);
    
    
    while(code!=4){
        
        switch(code){
                
            case 1:{
                int size,primary_key;
                cin>>size>>primary_key;
                h.insert(size,primary_key);
                break;
            }
            case 2:{
                h.display();
                break;
            }
            case 3:{
                int value;
                cin>>value;
                h.search(value);
            }
        }
        
        cin>>code;
    }
}
