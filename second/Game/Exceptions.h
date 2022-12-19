#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

namespace mtm
{
    class Exceptions: public std::exception
    {
        private:
        const char *massage;
        public:
        Exceptions(const char* error):massage(error){};
         virtual const char* what() const override noexcept
        {
            return massage;
        }
        
    };

    class IllegalCell : public Exceptions
    {
        public:
        IllegalCell():Exceptions("A game related error has occurred: IllegalCell"){};

    };
        class IllegalArgument : public Exceptions
    {
        public:
        IllegalArgument():Exceptions("A game related error has occurred: IllegalArgument"){};

    };
    class CellEmpty : public Exceptions
    {
        public:
        CellEmpty():Exceptions("A game related error has occurred: CellEmpty"){};

    };
    class MoveTooFar : public Exceptions
    {
        public:
        MoveTooFar():Exceptions("A game related error has occurred: MoveTooFar"){};

    };
    class CellOccupied : public Exceptions
    {
        public:
        CellOccupied():Exceptions("A game related error has occurred: CellOccupied"){};

    };
    class OutOfRange : public Exceptions
    {
        public:
        OutOfRange():Exceptions("A game related error has occurred: OutOfRange"){};

    };
    class OutOfAmmo : public Exceptions
    {
        public:
        OutOfAmmo():Exceptions("A game related error has occurred: OutOfAmmo"){};

    };
    class IllegalTarget : public Exceptions
    {
        public:
        IllegalTarget():Exceptions("A game related error has occurred: IllegalTarget"){};

    };
    
};

#endif //EXCEPTIONS_H_