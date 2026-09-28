
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../src/textnode.hpp"
//#include <catch2/catch_test_macros.hpp>

TEST_CASE("testing equals function")
{
    TextNode one("One", TextType::Text, "https://one.com");
    TextNode two("One", TextType::Text, "https://one.com");
    TextNode three("Three", TextType::Link, "https://three.com");

    CHECK(one.equals(two) == true);
    CHECK(one.equals(three) == false);
}

TEST_CASE("testing stringRepresentation function")
{
    TextNode testOne("This is the text one", TextType::Text, "https://text.com");
    TextNode testTwo("This is the bold one", TextType::Bold, "https://bold.com");
    TextNode testThree("This is the italic one", TextType::Italic, "https://italic.com");
    TextNode testFour("This is the code one", TextType::Code, "https://code.com");
    TextNode testFive("This is the link one", TextType::Link, "https://link.com");
    TextNode testSix("This is the image one", TextType::Image, "https://image.com");

    CHECK(testOne.stringRepresentation() == "TextNode(This is the text one, text, https://text.com)");
    CHECK(testTwo.stringRepresentation() == "TextNode(This is the bold one, bold, https://bold.com)");
    CHECK(testThree.stringRepresentation() == "TextNode(This is the italic one, italic, https://italic.com)");
    CHECK(testFour.stringRepresentation() == "TextNode(This is the code one, code, https://code.com)");
    CHECK(testFive.stringRepresentation() == "TextNode(This is the link one, link, https://link.com)");
    CHECK(testSix.stringRepresentation() == "TextNode(This is the image one, image, https://image.com)");
}
