easyOPAC Editorial Dashboard Notification
==========

Module extends Editorial Dashboard with possibility to send letters on node push (or other event) into ED.

## Requirements:
Editorial dashboard should be enabled.
Environment must fit phpmailer requirements (https://github.com/PHPMailer/PHPMailer).

## Configuration:
Enable module on @/admin/modules page.
Go to @/admin/config/editorial/dashboard_notification with admin configuration form.
Fill in required fields.

You have there two tables.
In first table with "Push" under "Action" header you can check roles
which will receive email when somebody pushes new node to editorial dashboard.
In second table you can select on which Editorial Dashboard events letters should be send.

## Usage:
