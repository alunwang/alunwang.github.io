
class MyString {
public:
    static size_t DCtor;    // Default constructor counter
    static size_t Ctor;     // constructor counter
    static size_t CCtor;    // copy-constructor counter
    static size_t CAsgn;    // copy-assignment counter
    static size_t MCtor;    // move-constructor counter
    static size_t MAsgn;    // move-assignment counter
    static size_t Dtor;     // destructor counter
private:
    char* _data;
    size_t _len;
    void _init_data(const char* s)
    {
        _data = new char[_len+1];
        memcpy(_data, s, _len);
        _data[_len] = '\0';
    }
public:
    // Default constructor
    MyString() : _data(NULL), _len(0) { ++DCtor; }
    // Constructor
    MyString(const char* p) : _len(strlen(p))
    {
        ++Ctor;
        _init_data(p);
    }
    // copy-constructor
    MyString(const MyString& str) : _len(str._len)
    {
        ++CCtor;
        _init_data(str._data);
    }
    // move-constructor, with "noexcept"
    MyString(MyString&& str) noexcept : _data(str._data), _len(str._len)
    {
        ++MCtor;
        str._len = 0;
        str._data = NULL;   // In case be deleted
    }
    // copy-assignment
    MyString& operator=(const MyString& str)
    {
        ++CAsgn;
        if (this != &str) {
            if (_data) delete _data;
            _len = str._len;
            _init_data(str._data);  // Copy
        } else {

        }
        return *this;
    }
    // move-assignment
    MyString& operator=(MyString&& str) noexcept
    {
        ++MAsgn;
        if (this != &str) {
            if (_data) delete _data;
            _len = str._len;
            _data = str._data;  // Move
            str._len = 0;
            str._data = NULL;   // In case be deleted
        }
        return *this;
    }
    // destructor
    ~MyString()
    {
        ++Dtor;
        if (_data) {
            delete _data;
        }
    }
    // <
    bool operator<(const MyString& rhs) const
    {
        return std::string(this->_data) < std::string(rhs._data);   // string already can compare
    }
    // ==
    bool operator==(const MyString& rhs) const
    {
        return std::string(this->_data) == std::string(rhs._data);  // string already can compare
    }
    //
    char* get() const
    {
        return _data;
    }
};

// Initialize static variables
size_t MyString::DCtor {0};
size_t MyString::Ctor {0};
size_t MyString::CCtor {0};
size_t MyString::CAsgn {0};
size_t MyString::MCtor {0};
size_t MyString::MAsgn {0};
size_t MyString::Dtor {0};

namespace std   // Must be put in std
{
template<>
struct hash<MyString> { // This is for unordered containers
    size_t operator()(const MyString& str) const noexcept
    {
        return hash<string>() (string(str.get());
    }
};
}