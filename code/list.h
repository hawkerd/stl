using namespace std;

template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}
};


template <typename T>
class List {
    private:
        Node<T>* head;
        Node<T>* tail;
        size_t _size;

    public:
        // empty container constructor
        List() : head(nullptr), tail(nullptr), _size(0) {}

        // fill constructor
        List(size_t size, const T& value) : head(nullptr), tail(nullptr), _size(0) {
            for (size_t i = 0; i < size; i++) {
                push_back(value);
            }
        }

        // range constructor
        List(const T* first, const T* last) : head(nullptr), tail(nullptr), _size(0) {
            for (const T* it = first; it != last; it++) {
                push_back(*it);
            }
        }

        // copy constructor
        List(const List& other) : head(nullptr), tail(nullptr), _size(0) {
            for (Node<T>* it = other.head; it != nullptr; it = it->next) {
                push_back(it->data);
            }
        }

        // move constructor
        List(List&& other) : head(other.head), tail(other.tail), _size(other._size) {
            other.head = nullptr;
            other.tail = nullptr;
            other._size = 0;
        }

        // initializer list constructor
        List(std::initializer_list<T> il) : head(nullptr), tail(nullptr), _size(0) {
            for (const T& value : il) {
                push_back(value);
            }
        }

        // destructor
        ~List() {
            Node<T>* curr = head;
            while (curr != nullptr) {
                Node<T>* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }

        // copy assignment
        List& operator=(const List& other) {
            // check for self assignment
            if (this == &other) {
                return *this;
            }

            // deallocate current contents
            clear();

            // copy contents
            for (Node<T>* it = other.head; it != nullptr; it = it->next) {
                push_back(it->data);
            }

            return *this;
        }

        // move assignment
        List& operator=(List&& other) {
            // check for self assignment
            if (this == &other) {
                return *this;
            }

            // deallocate current contents
            clear();

            // move contents
            head = other.head;
            tail = other.tail;
            _size = other._size;

            other.head = nullptr;
            other.tail = nullptr;
            other._size = 0;

            return *this;
        }

        // initializer list assignment
        List& operator=(std::initializer_list<T> il) {
            clear();

            // copy contents
            for (const T& value : il) {
                push_back(value);
            }

            return *this;
        }

        // capacity
        bool empty const noexcept {
            return _size == 0;
        }
        size_t size() const noexcept {
            return _size;
        }
        size_t max_size() const noexcept {
            return SIZE_MAX / sizeof(Node<T>);
        }

        // element access
        T& front() {
            if (head == nullptr) {
                throw out_of_range("List is empty");
            } else {
                return head->data;
            }
        }
        const T& front() const {
            return head->data;
        }
        T& back() {
            return tail->data;
        }
        const T& back() const {
            return tail->data;
        }

        // modifiers
        // assign - range
        template<typename InputIt>
        void assign(InputIt first, InputIt last) {
            clear();

            // assign new contents
            for (InputIt it = first; it != last; it++) {
                push_back(*it);
            }
        }

        // assign = fill
        void assign(size_t n, const T& val) {
            clear();

            // assign new contents
            for (size_t i = 0; i < n; i++) {
                push_back(val);
            }
        }

        // assign - initializer list
        void assign(std::initializer_list<T> il) {
            clear();

            // assign new contents
            for (const T& value : il) {
                push_back(value);
            }
        }

        // emplace
        void emplace_front(const T& value) {
            Node<T>* new_node = new Node<T>(value);
            if (head) {
                new_node->next = head;
                head->prev = new_node;
                head = new_node
            } else {
                head = new_node;
                tail = new_node;
            }
            _size++;
        }

        void emplace_back(const T& value) {
            Node<T>* new_node = new Node<T>(value);
            if (tail) {
                new_node->prev = tail;
                tail->next = new_node;
                tail = new_node;
            } else {
                head = new_node;
                tail = new_node;
            }
            _size++;
        }

        void 
        
        void clear() noexcept {
            Node<T>* curr = head;
            while (curr != nullptr) {
                Node<T>* temp = curr;
                curr = curr->next;
                delete temp;
            }

            head = nullptr;
            tail = nullptr;
            _size = 0;
        }

        // push



        void push_back(const T& value) {
            Node<T>* new_node = new Node<T>(value);

            // if the list is empty, set the head and tail to the new node
            if (head == nullptr) {
                head = new_node;
                tail = new_node;
            } else {
                tail->next = new_node;
                new_node->prev = tail;
                tail = new_node;
            }
        }
};