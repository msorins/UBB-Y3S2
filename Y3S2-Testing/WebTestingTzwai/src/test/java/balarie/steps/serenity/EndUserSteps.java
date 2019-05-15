package balarie.steps.serenity;

import balarie.pages.DictionaryPage;
import net.thucydides.core.annotations.Step;
import net.thucydides.core.steps.ScenarioSteps;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.containsString;
import static org.hamcrest.Matchers.hasItem;

public class EndUserSteps {

    DictionaryPage dictionaryPage;

    @Step
    public void is_the_home_page() {
        dictionaryPage.open();
    }

    @Step
    public void AddUser(String name, String email, String group, String tutor) {
        dictionaryPage.addStudent(name, email, group, tutor);
        assertThat("The reason behing this is to test that the student was added", dictionaryPage.getLastStudent().contains(name));
    }

    @Step
    public void DoNotAddUser(String name, String email, String group, String tutor) {
        dictionaryPage.addStudent(name, email, group, tutor);
        String ls = dictionaryPage.getLastStudent();
        assertThat("The reason behing this is to test that the student was added", !dictionaryPage.getLastStudent().contains(name));
    }


    @Step
    public String getLastStudent() {
        return dictionaryPage.getLastStudent();
    }


}