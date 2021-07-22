(function($) {

  // alter messages


      Drupal.evaluatePasswordStrength = function evaluatePasswordStrength(password, translate){
          Drupal.settings.password.tooShort     = "Password length must be between "+Drupal.settings.mo_2fa.passwordMinLength+" and "+Drupal.settings.mo_2fa.passwordMaxLength+" characters";
          Drupal.settings.password.addUpperCase = "Have at least one upper case letter";
          Drupal.settings.password.addLowerCase = "Have at least one lower case letter";
          Drupal.settings.password.addNumbers   = "Have at least one number";
          Drupal.settings.password.addPunctuation   = "Have at least one special character (#!%&$@)";
          Drupal.settings.password.sameAsUsername = "Password should not be same as username or email";
          let passwordMustNotBeNames = "Password should not be same as first name or last name";
          Drupal.settings.password.lastNUniquePassword = "The new password should not be same as your last "+Drupal.settings.mo_2fa.uniquePassword+" password(s)";
          password = $.trim(password);

          var weaknesses = 0, strength = 100, msg = [];

          var hasLowercase = /[a-z]+/.test(password);
          var hasUppercase = /[A-Z]+/.test(password);
          var hasNumbers = /[0-9]+/.test(password);
          var hasPunctuation = /[^a-zA-Z0-9]+/.test(password);

          // If there is a username edit box on the page, compare password to that, otherwise
          // use value from the database.
          var usernameBox = $("input.username");
          var username = (usernameBox.length > 0) ? usernameBox.val() : translate.username;



          if(document.getElementById("edit-mail")!=null){
              var email = document.getElementById("edit-mail").value  ;
          }
          else if(document.getElementById("edit-mail--2")!=null){
              var email = document.getElementById("edit-mail--2").value  ;
          }

          // Lose 5 points for every character less than 6, plus a 30 point penalty.
          if (password.length < Drupal.settings.mo_2fa.passwordMinLength || password.length > Drupal.settings.mo_2fa.passwordMaxLength) {
              msg.push("<span style='color:red;'>"+translate.tooShort+"</span>");
              strength -= ((Drupal.settings.mo_2fa.passwordMinLength - password.length) * 5) + 30;
          }
          else{
              msg.push("<span style='color:green;'>"+translate.tooShort+"</span>");
          }

          // Count weaknesses.
          if(Drupal.settings.mo_2fa.passwordMustHaveLowChar)
          {
            if (!hasLowercase  ) {
              msg.push("<span style='color:red;'>"+translate.addLowerCase+"</span>");
              weaknesses++;
            }
            else{
                msg.push("<span style='color:green;'>"+translate.addLowerCase+"</span>");
            }
          }
          if(Drupal.settings.mo_2fa.passwordMustHaveUpChar)
          {
            if (!hasUppercase  ) {
              msg.push("<span style='color:red;'>"+translate.addUpperCase+"</span>");
              weaknesses++;
            }
            else{
              msg.push("<span style='color:green;'>"+translate.addUpperCase+"</span>");
            }
          }
          
          if(Drupal.settings.mo_2fa.passwordMustHaveNumChar){
            if (!hasNumbers) {
              msg.push("<span style='color:red;'>"+translate.addNumbers+"</span>");
              weaknesses++;
            }
            else{
                msg.push("<span style='color:green;'>"+translate.addNumbers+"</span>");
            }
          }
          
          if(Drupal.settings.mo_2fa.passwordMustHaveSpecialChar){
            if (!hasPunctuation) {
              msg.push("<span style='color:red;'>"+translate.addPunctuation+"</span>");
              weaknesses++;
            }
            else{
              msg.push("<span style='color:green;'>"+translate.addPunctuation+"</span>");
            }  
          }
          


          // Apply penalty for each weakness (balanced against length penalty).
          switch (weaknesses) {
              case 1:
                  strength -= 12.5;
                  break;

              case 2:
                  strength -= 25;
                  break;

              case 3:
                  strength -= 40;
                  break;

              case 4:
                  strength -= 40;
                  break;
          }

          // Check if password is the same as the username.
        if(Drupal.settings.mo_2fa.passwordMustNotBeEmail)
        {
          if (password !== "" && (password.toLowerCase() === username.toLowerCase() || password.toLowerCase() === email.toLowerCase())) {
            // Passwords the same as username are always very weak.
            strength = 5;
            msg.push("<span style='color:red;'>"+translate.sameAsUsername+"</span>");
          }
          else{
            msg.push("<span style='color:green;'>"+translate.sameAsUsername+"</span>");
          }
        }
        if(Drupal.settings.mo_2fa.passwordMustNotBeFirstName || Drupal.settings.mo_2fa.passwordMustNotBeLastName)
        {
         
          if (password !== "" && (password.toLowerCase() === Drupal.settings.mo_2fa.fname.toLowerCase() || password.toLowerCase() === Drupal.settings.mo_2fa.lname.toLowerCase())) {
            // Passwords the same as username are always very weak.
            strength = 5;
            msg.push("<span style='color:red;'>"+passwordMustNotBeNames+"</span>");
          }
          else{
            msg.push("<span style='color:green;'>"+passwordMustNotBeNames+"</span>");
          }
        }
          // Based on the strength, work out what text should be shown by the password strength meter.
          if (strength < 60) {
              indicatorText = translate.weak;
          } else if (strength < 70) {
              indicatorText = translate.fair;
          } else if (strength < 80) {
              indicatorText = translate.good;
          } else if (strength <= 100) {
              indicatorText = translate.strong;
          }
          strength=Math.min(strength,75);


          isUniquePassword(password,translate,msg,strength,weaknesses);
          msg.push( "<span style='color:red;'>"+Drupal.settings.password.lastNUniquePassword+"</span>");




          // Assemble the final message.
          msg = translate.hasWeaknesses + '<ul style="line-height: 150%;"><li>' + msg.join('</li><li>') + '</li></ul>';
          return { strength: strength, message: msg, indicatorText: indicatorText };
      };
      function isUniquePassword(password,translate,msg,strength,weakness) {
          var handleAjaxCall = function (result) {
              var response = JSON.parse(result);

              var lastSuggestion = document.querySelector(".password-suggestions ul li:last-child span") ;
              var strengthIndicator = document.querySelector(".password-strength .password-indicator .indicator");
              //var submitButton = document.querySelector('#user-profile-form .form-submit');
              if(response.isUnique)
              {
                  // increase strength
                  lastSuggestion.style.color="green";
                  if( weakness===0 ){
                      strengthIndicator.style.width = "100%";
                  }
                  else
                  {
                      strengthIndicator.style.width = strength+20+"%";
                  }

              }
              else{

                  lastSuggestion.style.color="red";
              }



          }

          $.post(Drupal.settings.mo_2fa.uniquePasswordUrl, {"password": password, "ajaxCallId":Drupal.settings.mo_2fa.ajaxCallId}, handleAjaxCall);


      }


}(jQuery));
