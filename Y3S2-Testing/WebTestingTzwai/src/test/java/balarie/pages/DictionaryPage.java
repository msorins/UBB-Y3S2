package balarie.pages;

import net.thucydides.core.annotations.DefaultUrl;
import org.openqa.selenium.By;
import org.openqa.selenium.WebElement;
import net.serenitybdd.core.pages.WebElementFacade;
import java.util.stream.Collectors;

import net.serenitybdd.core.annotations.findby.FindBy;

import net.thucydides.core.pages.PageObject;

import java.util.List;

@DefaultUrl("http://127.0.0.1:4200")

public class DictionaryPage extends PageObject {

    @FindBy(id="nameId")
    private WebElementFacade nameField;

    @FindBy(id="emailId")
    private WebElementFacade emailField;

    @FindBy(id="groupId")
    private WebElementFacade groupField;

    @FindBy(id="tutorId")
    private WebElementFacade tutorField;

    @FindBy(id="addStudentId")

    private WebElementFacade addStudentButton;

    public void addStudent(String name, String email, String group, String tutor) {
        nameField.type(name);
        emailField.type(email);
        groupField.type(group);
        tutorField.type(tutor);
        addStudentButton.click();
    }

    public String getLastStudent() {
        WebElementFacade definitionList = find(By.id("students"));
        List<WebElement> elems = definitionList.findElements(By.tagName("li"));
        return elems.get( elems.size() - 1).getText();
    }
}