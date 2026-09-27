
#include "../src/textnode.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("stringRepresentation outputs", "[stringRepresentation]")
{
    TextNode testOne("This is the text one", TextType::Text, "https://text.com");
    TextNode testTwo("This is the bold one", TextType::Bold, "https://bold.com");
    TextNode testThree("This is the italic one", TextType::Italic, "https://italic.com");
    TextNode testFour("This is the code one", TextType::Code, "https://code.com");
    TextNode testFive("This is the link one", TextType::Link, "https://link.com");
    TextNode testSix("This is the image one", TextType::Image, "https://image.com");

    REQUIRE(testOne.stringRepresentation() == "TextNode(This is the text one, text, https://text.com)");
    REQUIRE(testTwo.stringRepresentation() == "TextNode(");
    REQUIRE(testThree.stringRepresentation() == "TextNode(");
    REQUIRE(testFour.stringRepresentation() == "TextNode(");
    REQUIRE(testFive.stringRepresentation() == "TextNode(");
    REQUIRE(testSix.stringRepresentation() == "TextNode(");
}
