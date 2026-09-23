
#define MD4QT_QT_SUPPORT
#include "md4qt/parser.h"
#include <iostream>

int main()
{
    std::cout << "It works!" << std::endl;
    MD::Parser<MD::QStringTrait> p;

    auto doc = p.parse(QStringLiteral("your_markdown.md"));
	
    for (auto it = doc->items().cbegin(), last = doc->items().cend(); it != last; ++it)
    {
        switch((*it)->type())
        {
            case MD::ItemType::Anchor :
            {
                auto a = static_cast< MD::Anchor< MD::QStringTrait >* > (it->get());
                qDebug() << a->label();
            }
                break;

            default :
                break;
        }
    }

    return 0;
}
