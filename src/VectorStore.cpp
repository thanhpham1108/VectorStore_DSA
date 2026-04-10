#include "VectorStore.h"

// ----------------- ArrayList Implementation -----------------

template <class T>
void ArrayList<T>::ensureCapacity(int cap){
    if(cap <= capacity) return;

    if(cap > capacity){

        int new_capacity =  max(cap ,(int)(capacity *1.5 )) ;
        
        T* new_data = new T[new_capacity];

        for(int i = 0; i < count; i++){
            new_data[i] = data[i];
        }
       delete[] data;
        data = new_data;
        capacity = new_capacity;
    }


}

template <class T>
ArrayList<T>::ArrayList(int initCapacity )
{

    if(initCapacity <  0) initCapacity = 10;
    
    data = new T[initCapacity];
    capacity = initCapacity;
    count = 0;

    // TODO
}

template <class T>
ArrayList<T>::ArrayList(const ArrayList<T> &other)
{ // deep copy

    
    this->capacity = other.capacity;
    this->count = other.count;

    T* new_data = new T[capacity+1];
    for(int i = 0; i < count; i++){
        new_data[i] = other.data[i];
    }

   
    data = new_data;

    // TODO
}
template <class T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& other){

    // check neu no khac hay khong
    if(this == &other) return *this;
    
        delete[] data;
        this->capacity = other.capacity;
        this->count = other.count;
        data = new T[capacity];

        for(int i = 0 ; i < count ; i++){
            data[i] = other.data[i];
        }

    
    return *this; // return object ArrayList, because this la` the pointer to the object ArrayList
}
template <class T>
ArrayList<T>::~ArrayList()
{
    // TODO
    delete[] data;
    
    data = nullptr;

    
}
template <class T>
void ArrayList<T>::add(T e){ // add at the end of the arrayList
    ensureCapacity(count  + 1);
    data[count] = e;
    count++;


}
template <class T>
void ArrayList<T>::add(int index, T e)
{
    if(index < 0 || index > count){
        throw out_of_range("This index is invalid!");
    }
    ensureCapacity(count +1);
    for(int i = count; i > index; i--){
        data[i] = data[i-1];
    }
    data[index] = e;
    count++;

}

template <class T>
T ArrayList<T>::removeAt(int index)
{
    if(index < 0 || index > count)
    {
        throw out_of_range("This index is invalid!");
    }
    // co 2 truonghop 1 la = 0 hoac la khac 0
    
    T removed = data[index];
    
        for(int i = index  ; i < count -1 ; i++)
        {
            data[i] = data[i+1];
// 0 1 2 3 4 5 6 7 8
// remove 3 
        }

        

    
    

    count--;
    return removed;
}
// TODO: implement other methods of ArrayList

template <class T>
bool ArrayList<T>::empty() const
{
    return count==0;

}

template <class T>
int ArrayList<T>::size() const
{
    return count;
}

template <class T>
void ArrayList<T>::clear()
{
    delete[] data;
    count = 0;
    capacity = 10;
    data = new T[capacity];

}

template <class T>
T& ArrayList<T>::get(int index) const
{
    if(index < 0 || index > count)
    {
        throw out_of_range("Index is invalid!");
    }
    
    return data[index];
}

template <class T>
void ArrayList<T>::set(int index, T e)
{
    if(index < 0 || index > count)
    {
        throw out_of_range("Index is invalid!");
    }
    data[index] = e;

}

template <class T>
int ArrayList<T>::indexOf(T item) const
{
    for(int i = 0; i < count; i++){
        if(data[i] == item) return i;
    }
    return -1;
}

template <class T>
bool ArrayList<T>::contains(T item) const
{
    for(int i = 0; i < count; i++)
    {
        if(data[i] == item) return 1;
    }
    return 0;
}

template <class T>
string ArrayList<T>::toString(string(*item2str)(T &)) const
{
    string result = "[";
    
    if(count == 0 ){
        result += "]";
        return result;
    }

    if(item2str == nullptr) {
    for(int k = 0; k < count -1 ; k++)
    {
        ostringstream os;
        os <<data[k];
        result += os.str();
        result += ", ";

    }
    ostringstream op;
    op << data[count -1];
    result += op.str(); // last element  if item2str chua dc declare
    
    } else {
        for(int j = 0 ; j < count - 1 ; j++)
        {
            result += item2str(data[j]);
            result += ", ";
        }
        result += item2str(data[count - 1 ]); // last element


    }


    result += "]";
    return result;

}





// ----------------- Iterator of ArrayList Implementation -----------------
template <class T>
ArrayList<T>::Iterator::Iterator(ArrayList<T> *pList, int index)
{
    // TODO
    if(pList == nullptr)
    {
        throw out_of_range("Pointer is nullptr");
    }
    if( index < 0 || index > pList->count)
    {
        throw out_of_range("Index is invalid!");
    }
    
    this->cursor = index;
    this->pList = pList;

}


template <class T>
typename  ArrayList<T>::Iterator& ArrayList<T>::Iterator::operator=(const Iterator &other)
{
    if(*this != other){
    this->cursor = other.cursor;
    this->pList = other.pList;
    }
    return *this;
}

template <class T>
T &ArrayList<T>::Iterator::operator*()
{
    if(cursor < 0 || cursor >= pList->count )
    {
        throw out_of_range("Iterator is out of range!");
    }

    return pList->data[cursor];

}

template <class T>
bool ArrayList<T>::Iterator::operator!=(const Iterator &other) const
{
    return (cursor != other.cursor || pList != other.pList);
}

template <class T>
typename ArrayList<T>::Iterator& ArrayList<T>::Iterator::operator++()
{
    if(cursor == pList->count)
    {
        throw out_of_range("Iterator cannot advance past end!");
    }
    cursor++;
    return *this;

}
template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::Iterator::operator++(int)
{
    if(cursor >= pList->count)
    {
        throw out_of_range("Iterator cannot advance past end!");
    }
    Iterator temp = *this;
    cursor++;
    return temp;
}

template <class T>
typename ArrayList<T>::Iterator& ArrayList<T>::Iterator::operator--()
{
    if(cursor == 0)
    {
        throw out_of_range("Iterator cannot move before begin!");
    }
    cursor--;
    return *this;
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::Iterator::operator--(int)
{
    if(cursor == 0)
    {
        throw out_of_range("Iterator cannot move before begin!");
    }
    Iterator temp = *this;
    cursor--;
    return temp;
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::begin()
{
    return Iterator(this, 0);
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::end()
{
    return Iterator(this, count);
}



// ----------------- SinglyLinkedList Implementation -----------------
template <class T>
SinglyLinkedList<T>::SinglyLinkedList()
{
    head = nullptr;
    tail = nullptr;
    count = 0;

    // TODO
}

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
    clear();


    // TODO
}

template <class T>
void SinglyLinkedList<T>::add(T e)
{
    Node* newNode = new Node(e);
    if(head == nullptr) // danh sach rong
    {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;

    }


    count++;
}

template <class T>
void SinglyLinkedList<T>::add(int index , T e)
{
    if(index < 0 || index > count ){
        throw out_of_range("Index is invalid!");
    }

    Node* newNode = new Node(e);
        if (index == 0) { // insert at head
        newNode->next = head;
        head = newNode;
        if (count == 0) tail = newNode; // first element
    } else if (index == count) { // insert at tail
        tail->next = newNode;
        tail = newNode;
    } else { // insert in the middle
        Node* cur = head;
        for (int i = 0; i < index - 1; i++) {
            cur = cur->next;
        }
        newNode->next = cur->next;
        cur->next = newNode;
    }

    count++;
}

template <class T>
T SinglyLinkedList<T>::removeAt(int index)
{
    if(index < 0 || index >= count){
        throw out_of_range("Index is invalid!");
    }

    Node* cur = head;
    Node* prev = nullptr;
   
   

    for(int i = 0; i < index ; i++){
        prev = cur;
        cur = cur->next;

    }
    T removed = cur -> data;
    if(prev == nullptr) {
        // remove head
        head = cur->next;
        if(head == nullptr) tail = nullptr;// list empty
    } else {
        prev -> next = cur->next;
        if(cur == tail ) tail = prev;
    }
    delete cur;

   

    count--;

    return removed;
}

template <class T>
bool SinglyLinkedList<T>::removeItem(T item){
    Node* cur = head;
    int index = 0;
    if(cur == nullptr) return 0;

    while(cur != nullptr ){
        
        if(cur->data == item){
            removeAt(index);
            return 1;
        }
        cur = cur->next;
        index++;
    }
    
   
    return 0;
    
}


template <class T>
bool SinglyLinkedList<T>::empty() const {
    return (count==0);

}

template <class T>
int SinglyLinkedList<T>::size() const {

    return count;
}

template <class T>
void SinglyLinkedList<T>::clear(){

   Node* cur = head;
   while ( cur != nullptr){
    Node* next = cur->next;
    delete cur;
    cur = next;
   }
   head = tail = nullptr;
   count =0;

}

template <class T>
T& SinglyLinkedList<T>::get(int index) const {
    if(index < 0 || index >= count){
        throw out_of_range("Index is invalid!");
    }
    Node* cur = head;
  
        for(int i = 0 ; i < index ; i++){
            cur = cur->next;
        }
     
    

    return cur->data;
}

template <class T>
int SinglyLinkedList<T>::indexOf(T item) const
{
int index = -1;
Node* cur = head;
int i =0;
while( cur != nullptr){
    if(cur->data == item){
        index = i;
        break;
    }
    i++;
    cur = cur->next;

}

return index;
}

template <class T>
bool SinglyLinkedList<T>::contains(T item) const
{
    Node* cur = head;
    if(head == nullptr) return 0;

    while(cur != nullptr){
        if(cur->data == item ){
            return 1;
        }   
        cur = cur->next;
     }

     return 0;
}
/*
template <class T>
string SinglyLinkedList<T>::toString(string (*item2str)(T&)) const
{
    string result = "";

    
   
    Node* cur = head;
    while( cur != nullptr){
        // Truong hop neu kh co item2str
        result += "[";
        if(item2str == nullptr){
        
            ostringstream os;
            os << cur ->data;
            result += os.str();
        

        
        } else { // neu co item2str
            result += item2str(cur->data);

        }
        result += "]";
        if(cur->next != nullptr ){
            // neu chua phai la last node
            result += "->";
        }
        cur = cur->next;


    }
    if(count == 0){ // empty head
        result = "[]";
        return result;
    }

    return result;
}

*/

/*
template <class T>
string SinglyLinkedList<T>::toString(string (*item2str)(T&)) const {
    // If no formatter is provided, tests expect an empty string
    if (item2str == nullptr) return "";

    // Empty list with a formatter: tests also expect an empty string
    if (count == 0) return "";

    // Non-empty list with a formatter: format as [x]->[y]->...
    string result;
    Node* cur = head;
    while (cur != nullptr) {
        result += "[";
        result += item2str(cur->data);
        result += "]";
        if (cur->next != nullptr) result += "->";
        cur = cur->next;
    }
    return result;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
string SinglyLinkedList<T>::toString(string (*item2str)(T&)) const {
    Node* current = head;
    if (current == nullptr) return "";
    stringstream ss;
    while (current != nullptr) {
        if (item2str != nullptr) {
            ss << "[" << item2str(current->data) << "]";
        } else {
            ss << "[" << current->data << "]";
        }
        
        if (current->next != nullptr) {
            ss << "->";
        }
        current = current->next;
    }
    
    return ss.str();
}




*/

template <class T>
string SinglyLinkedList<T>::toString(string (*item2str)(T&)) const {
    if (head == nullptr) {
        return "";  // empty SSL returns ""
    }

    stringstream ss;
    Node* current = head;
    while (current != nullptr) {
        if (item2str) {
            ss << "[" << item2str(current->data) << "]";
        } else {
            ss << "[" << current->data << "]";  // default to operator<<
        }

        if (current->next != nullptr) {
            ss << "->";
        }
        current = current->next;
    }
    return ss.str();
}




// TODO: implement other methods of SinglyLinkedList

// ----------------- Iterator of SinglyLinkedList Implementation -----------------
template <class T>
SinglyLinkedList<T>::Iterator::Iterator(Node *node)
{
    
    current = node;
    // TODO
}

template <class T>
typename SinglyLinkedList<T>::Iterator& SinglyLinkedList<T>::Iterator::operator=( const Iterator& other){

    if(other.current != nullptr && other.current != current){
        current = other.current;
    }
    return *this;

}

template <class T>
T& SinglyLinkedList<T>::Iterator::operator*()
{
    if(current == nullptr){
        throw out_of_range("Iterator is out of range!");

    }

    return current -> data;



}

template <class T>
bool SinglyLinkedList<T>::Iterator::operator!=(const Iterator& other) const {
    return current != other.current;
}


template <class T>
typename SinglyLinkedList<T>::Iterator& SinglyLinkedList<T>::Iterator::operator++(){
if(current  == nullptr){
    throw out_of_range("Iterator cannot advance past end!");
}
current = current -> next;
return *this;

}

template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::Iterator::operator++(int){
    if(current  == nullptr){
        throw out_of_range("Iterator cannot advance past end!");
    }
    Iterator temp = *this;
    current = current->next;
    return temp;
}

template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::begin(){
    return Iterator(head);
}

template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::end(){
    return Iterator(nullptr);
}

// ----------------- VectorStore Implementation -----------------
int VectorStore::nextId = 0;


VectorStore::VectorStore(int dimension , EmbedFn embeddingFunction ) {
    // TODO
    this->dimension = dimension;
    this->embeddingFunction = embeddingFunction;
    this->count = 0;
    
    this->nextId = 1; // khoi tao = 1 luon./

    
 } 



VectorStore::~VectorStore() {
    // TODO
    clear();

}

int VectorStore::size() const{
    return count;

}

bool VectorStore::empty() const {
    return (count==0);
}

void VectorStore::clear(){
    int n = records.size();
    for(int k = 0 ; k < n ; k++){
        VectorRecord* rec = records.get(k);
        delete rec->vector;
        delete rec;

    }

    records.clear();
    
    count = 0;
    // embeddingFunction = nullptr;
    // Khong xoa embeddingFunction


}

SinglyLinkedList<float>* VectorStore::preprocessing(string rawText){
    if(embeddingFunction == nullptr){
        throw runtime_error("Embedding fnction is not set!!!");

    }
    // Call embedding function to get the first vector
    SinglyLinkedList<float>* vect = embeddingFunction(rawText);
    //Lay 
    int dimen = vect->size();
    // thuc hien dieu kien

    while(dimen > dimension) // cat phan o cuoi neu lon hon
    {
        vect->removeAt(dimen -1 );
        dimen--;
    }
    while(dimen < dimension) // them 0.0 o cuoi
    {
        vect->add(0.0f);
        dimen++;
    }
    
    return vect;

}


void VectorStore::addText(string rawText){
     int newId;

     if(count == 0){
        nextId = 1;
        newId = nextId;

     }else {
        newId = nextId;
     }

    SinglyLinkedList<float>* vector = preprocessing(rawText);

    VectorRecord* new_recod = new VectorRecord(nextId++, rawText, vector);
    records.add(new_recod);

    nextId = newId+1;
    count +=1;

}




VectorStore::VectorRecord* VectorStore::getRecord(int index) const {
    
    return records.get(index);
}

SinglyLinkedList<float>& VectorStore::getVector(int index)  const
{

    kiemtraIndex(index);
    return *getRecord(index)->vector;

}

string VectorStore::getRawText(int index) const {
    kiemtraIndex(index);
    return getRecord(index)->rawText;

}

int VectorStore::getId(int index) const 
{
    kiemtraIndex(index);
    return getRecord(index) -> id;
}

bool VectorStore::removeAt(int index)
{
    kiemtraIndex(index);
    
    // lay vectorrecord ra

    VectorRecord*  record = records.get(index);

    delete record->vector;

    delete record;
    records.removeAt(index);

    count--;

    return 1;

}



bool VectorStore::updateText(int index, string newRawText){
    kiemtraIndex(index);

    VectorRecord* reco = records.get(index);
    SinglyLinkedList<float>* new_vect = preprocessing(newRawText);

    delete reco->vector;
    reco ->rawText = newRawText;
    reco->rawLength = newRawText.length();
    reco->vector = new_vect;

    return true;


}


void VectorStore::setEmbeddingFunction(SinglyLinkedList<float>*  (*newEmbeddingFunction)(const
 string&)){
    this->embeddingFunction = newEmbeddingFunction;


 }


void VectorStore::forEach(void (*action)(SinglyLinkedList<float>&, int id, string&)) {
    for (int i = 0; i < count; i++) {
        VectorRecord* record  = records.get(i);
        action(*record->vector, record->id, record->rawText);

    }
}

double VectorStore::cosineSimilarity(const SinglyLinkedList<float>& v1, const SinglyLinkedList<float>& v2) const
{

    if(v1.size() != v2.size()){
        throw invalid_argument("Vectors have dif dimension!!");

    }

      if (v1.size() == 0 || v2.size() == 0) {
        return 0.0;
    }

    // Tich vo huong'
    double dotProduct = 0.0;
    for(int i = 0 ; i < v1.size(); i++){
        dotProduct+= v1.get(i) * v2.get(i);
    }

    // Tinh tri tuyet doi
    double mag1 = 0.0;
    double mag2 =0.0;
    for(int i = 0 ; i < v1.size() ;i++){
        mag1 += v1.get(i) * v1.get(i);
        mag2 += v2.get(i) * v2.get(i);
    }
    mag1 = sqrt(mag1);
    mag2 = sqrt(mag2);

    // Check neu' co mag nao = 0 thi out 
    if(mag1 == 0.0 || mag2 == 0.0){
        return 0.0;
    }

    return dotProduct/(mag1*mag2);


}


double VectorStore::l1Distance(const SinglyLinkedList<float>& v1, const SinglyLinkedList<float>& v2) const
{
    if(v1.size() != v2.size() ){
        throw invalid_argument("Vectors have different lengt");
    }

    if(v1.size() == 0 || v2.size() == 0) return 0.0;

    double dist = 0.0;
    // Chay tu dau den' cuoi de lay float cua tung i
    for(int k = 0 ; k < v1.size(); ++k){
        dist += abs( (v1.get(k)) - (v2.get(k)) );
    }    

    return dist;
}

double VectorStore::l2Distance(const SinglyLinkedList<float>& v1, const SinglyLinkedList<float>& v2) const 
{
    // Edge case if vector is not the same  size
    if(v1.size() != v2.size()){
        throw invalid_argument("Different size");
    }
    if(v1.size() == 0 || v2.size() == 0) return 0.0;

    double Eudist = 0.0;

    for(int i = 0 ; i < v1.size() ; i++){
        Eudist += pow((v1.get(i) - v2.get(i) ) , 2 );

    }

    Eudist = sqrt(Eudist);

    return Eudist;




}



int VectorStore::findNearest(const SinglyLinkedList<float> &query, const string &metric) const
{

   if (metric != "cosine" && metric != "euclidean" && metric != "manhattan") {
     throw invalid_metric("Unknown metric!");    
}
    if(query.size() == 0){
        throw invalid_metric("Query is empty!");
    }

    int nearest = -1;
    double minDist = numeric_limits<double>::infinity(); // So vo cuc, de de~ tim so be hon hon

    if(metric == "cosine"){
        minDist = -2.0; 
    }
    for(int i = 0; i < count; i++){

        SinglyLinkedList<float>& currentVect = getVector(i);

        double distance = 0.0;
        
        if (metric == "cosine") {
    double similarity = cosineSimilarity(query, currentVect);
    if (similarity > minDist) {  // Sua de max similarity
        minDist = similarity;
        nearest = i;
        }
    } else if(metric == "euclidean") {
            distance = l2Distance(query, currentVect);
            if(distance < minDist){
                minDist = distance ;
                nearest = i;

            }
        } else if( metric == "manhattan"){
            distance = l1Distance(query, currentVect);
            if(distance < minDist){
                minDist = distance;
                nearest = i;

            }
        }
    }

    return nearest;


}

int* VectorStore::topKNearest(const SinglyLinkedList<float>& query, int k, const string& metric) const {
    // Validate metric
    if (metric != "cosine" && metric != "euclidean" && metric != "manhattan") {
        throw invalid_metric("Unknown metric!");
    }

    // Validate k
    if (k <= 0 || k > count) {
        throw invalid_k_value("Invalid k value");
    }

    struct PairDI {
        double score; 
        int idx;
    };

    int n = count;
    PairDI* arr = new PairDI[n];

    // Calculate the score for each record
    if (metric == "cosine") {
        for (int i = 0; i < n; i++) {
            double sim = cosineSimilarity(query, *records.get(i)->vector);
            // For cosine: higher is better, but we’ll store as negative so smaller = better
            arr[i].score = -sim;
            arr[i].idx   = i;
        }
    } else if (metric == "euclidean") {
        for (int i = 0; i < n; i++) {
            double dist = l2Distance(query, *records.get(i)->vector);
            arr[i].score = dist; // smaller distance = better
            arr[i].idx   = i;
        }
    } else { // manhattan
        for (int i = 0; i < n; i++) {
            double dist = l1Distance(query, *records.get(i)->vector);
            arr[i].score = dist;
            arr[i].idx   = i;
        }
    }

    // Sort array by score ascending
    std::sort(arr, arr + n, [](const PairDI& a, const PairDI& b) {
        if (a.score == b.score) return a.idx < b.idx; // tie-breaker: smaller index first
        return a.score < b.score;
    });

    // Collect top k indices
    int* result = new int[k];
    for (int i = 0; i < k; i++) {
        result[i] = arr[i].idx;
    }

    delete[] arr;
    return result;
}


/*
int* VectorStore::topKNearest(const SinglyLinkedList<float>& query, int k, const string& metric) const {
    // Validate metric
    if (metric != "cosine" && metric != "euclidean" && metric != "manhattan") {
        throw invalid_metric("Unknown metric!");
    }

    // Validate k
    if (k <= 0 || k > count) {
        throw invalid_k_value("Invalid k value");
    }

    // Prepare array of PairDI to store score and index
    struct PairDI { 
        double score; 
        int idx; 
    };

    int n = count;
    PairDI* arr = new PairDI[n];

    // Calculate the score (distance or similarity) based on the metric
    if (metric == "cosine") {
        for (int i = 0; i < n; ++i) {
            arr[i].score = -cosineSimilarity(query, *records.get(i)->vector);  // Negate for ascending order
            arr[i].idx   = i;
        }
    } else if (metric == "euclidean") {
        for (int i = 0; i < n; ++i) {
            arr[i].score = l2Distance(query, *records.get(i)->vector); // Smaller distance is better
            arr[i].idx   = i;
        }
    } else { // "manhattan"
        for (int i = 0; i < n; ++i) {
            arr[i].score = l1Distance(query, *records.get(i)->vector); // Smaller distance is better
            arr[i].idx   = i;
        }
    }

    // Sort all the PairDI elements by score (ascending for distance, descending for similarity)
    std::sort(arr, arr + n, [](const PairDI& a, const PairDI& b) {
        return a.score < b.score;  // Sort by score
    });

    // Allocate memory for the result array and fetch the top k indices
    int* result = new int[k];
    for (int i = 0; i < k; ++i) result[i] = arr[i].idx;

    

    delete[] arr;  // Free the allocated memory for PairDI array

    return result;
}

*/



// TODO: implement other methods of VectorStore


// Explicit template instantiation for char, string, int, double, float, and Point

template class ArrayList<char>;
template class ArrayList<string>;
template class ArrayList<int>;
template class ArrayList<double>;
template class ArrayList<float>;
template class ArrayList<Point>;

template class SinglyLinkedList<char>;
template class SinglyLinkedList<string>;
template class SinglyLinkedList<int>;
template class SinglyLinkedList<double>;
template class SinglyLinkedList<float>;
template class SinglyLinkedList<Point>;
