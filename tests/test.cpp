
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../src/textnode.hpp"
#include "../src/leafnode.hpp"
#include "../src/parentnode.hpp"
//#include <catch2/catch_test_macros.hpp>

TEST_CASE("testing TextNode equals() function")
{
    TextNode one("One", TextType::Text, "https://one.com");
    TextNode two("One", TextType::Text, "https://one.com");
    TextNode three("Three", TextType::Link, "https://three.com");

    CHECK(one.equals(two) == true);
    CHECK(one.equals(three) == false);
}

TEST_CASE("testing TextNode stringRepresentation() function")
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

TEST_CASE("testing TextNode splitNodesDelimiter() function")
{
    TextNode nodeOne("This is text with a `code block` word", TextType::Text);
    std::vector<TextNode> nodeOneSplit = {TextNode("This is text with a ", TextType::Text),
        TextNode("code block", TextType::Code),
        TextNode(" word", TextType::Text)};

    TextNode node1("This is `code`", TextType::Text);
    TextNode node2("This is `code` and `more`", TextType::Text);
    TextNode node3("`code`", TextType::Text);
    TextNode node4("plain text", TextType::Text);
    TextNode node5("This is `unclosed", TextType::Text);
    TextNode node6("", TextType::Text);
    std::vector<TextNode> nodesTwo = {node1, node2, node3, node4, node5, node6};
    std::vector<TextNode> nodesTwoSplit = {};

    CHECK(nodeOne.splitNodesDelimiter({nodeOne}, "`", TextType::Code) == nodeOneSplit);
    CHECK(node1.splitNodesDelimiter(nodesTwo, "`", TextType::Code) == nodesTwoSplit);
}

TEST_CASE("testing ParentNode toHTML() function with children")
{
    LeafNode childNode("span", "child");
    ParentNode parentNode("div", {childNode});

    CHECK(parentNode.toHTML() == "<div><span>child</span></div>");
}

TEST_CASE("testing ParentNode toHTML() function with grandchildren")
{
    LeafNode grandchildNode("b", "grandchild");
    ParentNode childNode("span", {grandchildNode});
    ParentNode parentNode("div", {childNode});

    CHECK(parentNode.toHTML() == "<div><span><b>grandchild</b></span></div>");
}

TEST_CASE("testing ParentNode toHTML() function with multiple element map")
{
    LeafNode bold("b", "Bold text");
    LeafNode normal("", "Normal text");
    LeafNode italic("i", "italic text");
    
    ParentNode parentNode("p", {bold, normal, italic, normal});

    CHECK(parentNode.toHTML() == "<p><b>Bold text</b>Normal text<i>italic text</i>Normal text</p>");
}

TEST_CASE("testing ParentNode toHTML() function with multiple grandchildren")
{
    LeafNode grandOne("p", "grandchild one");
    LeafNode grandTwo("b", "grandchild two");
    LeafNode grandThree("i", "grandchild three");

    ParentNode childOne("div", {grandOne});
    ParentNode childTwo("span", {grandTwo});
    ParentNode childThree("body", {grandThree});

    ParentNode parentNode("br", {childOne, childTwo, childThree});

    CHECK(parentNode.toHTML() == "<br></br>");
}
