
#ifndef __SE__CHEESEBOARD_HPP__
#define __SE__CHEESEBOARD_HPP__

#include "FbLinux.hpp"

namespace se
{
    class CheeseBoard : public FbLinux
    {
    public:
        void Draw32CheeseBoard(const int & boxSize = 6);
        void Draw16CheeseBoard(const int & boxSize = 6);
    };
}

#endif // __SE__CHEESEBOARD_HPP__
