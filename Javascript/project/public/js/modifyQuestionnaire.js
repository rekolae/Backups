$(document).ready(function() {

    // Disable question delete button, qhen only one question is present
    let question_amount = $("div.card.mb-1.mt-1").length;
    if (question_amount <= 1) {
        $("button[id$='deleteQuestion']").addClass("disabled");
        $("button[id$='deleteQuestion']").attr("disabled", "disabled");
    }

    else {
        $("button[id$='deleteQuestion']").removeClass("disabled");
        $("button[id$='deleteQuestion']").removeAttr("disabled");
    }

    // Remove the added question or choice
    $(document).on('click', "button[id*='Added']", function() {
        let type = $(this).data('type');

        if (type === "question") {
            $(this).parent().parent().parent().remove();
        }

        else if (type === "choice") {
            $(this).parent().parent().remove();
        }
    });

    // Handels adding new choices to the right question
    $(document).on('click', "[id$='addChoice']", function() {
        let question = $(this).parent().prev().attr("id").split(".")[0].split("_");
        let question_num = parseInt(question[1], 10);

        let choice = $(this).parent().prev().attr("id").split(".")[1].split("_");
        let choice_num = parseInt(choice[1], 10);
        choice_num += 1;

         $(this).parent().before(
            `
            <!-- Question #${question_num} choice #${choice_num} -->
            <div id="Q_${question_num}.C_${choice_num}" class="form-row mb-2">
                <div class="form-group col">
                    <label for="Q_${question_num}.C_${choice_num}.title">Choice</label>
                    <input type="text" class="form-control" id="Q_${question_num}.C_${choice_num}.title" name="Q_${question_num}.C_${choice_num}.title" placeholder="Something something?">
                </div>
                <div class="form-group col">
                    <label for="Q_${question_num}.C_${choice_num}.correctness">Correctness</label>
                    <select id="Q_${question_num}.C_${choice_num}.correctness" name="Q_${question_num}.C_${choice_num}.correctness" class="form-control">
                        <option value="true">True</option>
                        <option value="false">False</option>
                    </select>
                </div>
                <div class="form-group col">
                    <label for="Q_${question_num}.C_${choice_num}.hint">Hint</label>
                    <input type="text" class="form-control" id="Q_${question_num}.C_${choice_num}.hint" name="Q_${question_num}.C_${choice_num}.hint" placeholder="Hint hint ;)">
                </div>
                <div>
                    <button id="Q_${question_num}.C_${choice_num}.deleteAdded" type="button" class="btn btn-outline-danger" style="margin-top: 70%" data-type="choice"><i class="fas fa-backspace"></i></button>
                </div>
            </div>
            `
         );
    });

    // Handles adding new questions
    $("#addQuestion").click(function() {

        let question = $(this).parent().prev().attr("id").split("_");
        let question_num = parseInt(question[1], 10);
        question_num += 1;

         $("button#addQuestion").parent().before(
            `
            <!-- Question #${question_num} title and maximum points -->
            <div id="Q_${question_num}" class="card mb-1 mt-1">
                <div class="card-body" id="Q_${question_num}.body">
                    <div class="form-row mb-2">
                        <div class="form-group col-md-8">
                            <label for="Q_${question_num}.title">Question title</label>
                            <input type="text" class="form-control" id="Q_${question_num}.title" name="Q_${question_num}.title" placeholder="Another unique and fabulous title">
                        </div>
                        <div class="form-group col-md-4">
                            <label for="Q_${question_num}.maxPoints">Max points</label>
                            <input type="text" class="form-control" id="Q_${question_num}.maxPoints" name="Q_${question_num}.maxPoints" placeholder="666">
                        </div>
                    </div>

                    <!-- Question #${question_num} choice #0 -->
                    <div id="Q_${question_num}.C_0" class="form-row mb-2">
                        <div class="form-group col">
                            <label for="Q_${question_num}.C_0.title">Choice</label>
                            <input type="text" class="form-control" id="Q_${question_num}.C_0.title" name="Q_${question_num}.C_0.title" placeholder="Something something?">
                        </div>
                        <div class="form-group col">
                            <label for="Q_${question_num}.C_0.correctness">Correctness</label>
                            <select id="Q_${question_num}.C_0.correctness" name="Q_${question_num}.C_0.correctness" class="form-control">
                                <option value="true">True</option>
                                <option value="false">False</option>
                            </select>
                        </div>
                        <div class="form-group col">
                            <label for="Q_${question_num}.C_0.hint">Hint</label>
                            <input type="text" class="form-control" id="Q_${question_num}.C_0.hint" name="Q_${question_num}.C_0.hint" placeholder="Hint hint ;)">
                        </div>
                        <div>
                            <button id="Q_${question_num}.C_0.deleteAdded" type="button" class="btn btn-outline-danger" style="margin-top: 70%" data-type="choice"><i class="fas fa-backspace"></i></button>
                        </div>
                    </div>

                    <!-- Question #${question_num} choice #1 -->
                    <div id="Q_${question_num}.C_1" class="form-row mb-2">
                        <div class="form-group col">
                            <label for="Q_${question_num}.C_1.title">Choice</label>
                            <input type="text" class="form-control" id="Q_${question_num}.C_1.title" name="Q_${question_num}.C_1.title" placeholder="Something something?">
                        </div>
                        <div class="form-group col">
                            <label for="Q_${question_num}.C_1.correctness">Correctness</label>
                            <select id="Q_${question_num}.C_1.correctness" name="Q_${question_num}.C_1.correctness" class="form-control">
                                <option value="true">True</option>
                                <option value="false">False</option>
                            </select>
                        </div>
                        <div class="form-group col">
                            <label for="Q_${question_num}.C_1.hint">Hint</label>
                            <input type="text" class="form-control" id="Q_${question_num}.C_1.hint" name="Q_${question_num}.C_1.hint" placeholder="Hint hint ;)">
                        </div>
                        <div>
                            <button id="Q_${question_num}.C_1.deleteAdded" type="button" class="btn btn-outline-danger" style="margin-top: 70%" data-type="choice"><i class="fas fa-backspace"></i></button>
                        </div>
                    </div>
                    <div>
                        <button id="Q_${question_num}.addChoice" type="button" class="btn btn-outline-primary float-left"><i class="fas fa-plus-square"></i> Add choice</button>
                        <button id="Q_${question_num}.deleteQuestionAdded" type="button" class="btn btn-outline-danger float-right" data-type="question"><i class="fas fa-file-excel"></i> Delete Question</button>
                    </div>
                </div>
            </div>
            `
         );
    });
});
