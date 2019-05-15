package balarie.features.search;

import balarie.steps.serenity.EndUserSteps;
import net.serenitybdd.junit.runners.SerenityParameterizedRunner;
import net.thucydides.core.annotations.Managed;
import net.thucydides.core.annotations.Steps;
import net.thucydides.junit.annotations.UseTestDataFrom;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.openqa.selenium.WebDriver;

@RunWith(SerenityParameterizedRunner.class)
@UseTestDataFrom("/Users/so/Desktop/Y3S2/Y3S2-Testing/WebTestingTzwai/src/test/resources/features/search/notest.txt")
public class TestDoNotAddStudentWeb {

    @Managed(uniqueSession = true)
    public WebDriver webdriver;

    @Steps
    public EndUserSteps anna;

    public String name;
    public String email;
    public String group;
    public String tutor;


    @Test
    public void addStudentIncorect() {
        anna.is_the_home_page();
        anna.DoNotAddUser("Naomi", "naomi@gmail.com", "alabama", "Cipri Tutorele");
    }

    public String getName() {
        return this.name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getEmail() {
        return this.email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getGroup() {
        return this.group;
    }

    public void setGroup(String group) {
        this.group = group;
    }

    public String getTutor() {
        return this.tutor;
    }

    public void setTutor(String tutor) {
        this.tutor = tutor;
    }

} 