#include <stdio.h>
#include <string.h>

//function declaration
double atof(); //to convert char value to float
void add_details();
void selling_mode();
void shop_details();
void cashier_details();
void header_bill();
void footer_bill();
void list();

int main()
{
  int select;
  int choice;
  
  //select shop management or customer selling mode
  printf("\n\nEnter 1 to manage shop detais--->\n");
  printf("Enter 2 to selling mode--------->\n\n");
  printf("Enter your choice:\n");
  scanf("%d", &select);

  switch (select)
  {
  case 1://shop management 
    printf("Press 0 to display item details-------------->\n");
    printf("Press 1 to edit shop details----------------->\n");
    printf("Press 2 to change cashier details------------>\n");
    printf("Press 3 to add new items to store------------>\n");
    printf("Press 4 to back------------------------------>\n");
    printf("Select your choice:\n");
    scanf("%d", &choice);

    switch (choice)
    {

    case 0:
    //show item list in store to cashier
      list();
      main();
    case 1:
    //edit shop details
      shop_details();
      main();
      break;

    case 2:
    //edit cashier name and date
      cashier_details();
      main();
      break;

    case 3:
    //add new items to store
      add_details();
      main();
      break;

    case 4:
    //back to main menu
      main();
      break;
    }
    break;

  case 2: //when selling items to customer(selling mode)
    list();
    selling_mode();
    break;
  }

  return 0;
}

void add_details()  //add new items 
{
  int item_count = 0;

  char item_name[50];
  char item_code[50];
  char item_price[50];

  FILE *fptr;
  char filename[50];

  strcpy(filename, "item_details");
  fptr = fopen(filename, "a"); //open item details file to add items

  getchar();
  {
    fflush(stdin); 
    printf("\nEnter item Name : ");
    scanf("%[^\n]s", item_name); //enter item name

    printf("\nEnter item price:");
    scanf("%s", item_price); //enter item price

    printf("\nEnter item code : ");
    scanf("%s", item_code); //enter item code

    fprintf(fptr, "%s,%s,%s\n", item_code, item_name, item_price); //print to file 

    fclose(fptr); //close file to save
  }

  main();
}

void selling_mode()
{

  char copy1[20];
  int count = 0;
  const char s[2] = ","; 
  char *token;
  char item_code_id[50];
  double x;
  int qunt;
  double add;
  double add2 = 0;
  FILE *bill;
  float cash;
  float cash2;

  while (1)
  {
    //if item code is correct item will add to bill & if  enter 0 bill will be created
    printf("\n\nEnter item code to add more items to bill/Enter 0 to get bill: "); 
    scanf("%s", item_code_id);
    //Enter "0" to create bill
    if (!strcmp(item_code_id, "0")) //compare the item code id and if it is "0" create the bill
    {
      printf("Total Amount: Rs.%.2f", add2);
      printf("\nEnter cash amount: Rs."); //enter customer cash amount
      scanf("%f", &cash);

      if (cash < add2) //if cash not enough
      {
        printf("The cash amount is not enough to pay bill !!!!\n");
        printf("Please enter new cash amount :Rs."); 
        scanf("%f", &cash2);  // new cash amount
        header_bill(); //header bill will print here
        
        
        printf("\n================================================================================================\n");
        printf("%-40s%15s%17s%17s\n", "Item", "Unit Price", "Qty", "Amount");
        printf("%55s%34s\n", "(Rs.)", "(Rs.)");
        printf("================================================================================================\n\n");

        const char filename[] = "bill";
        FILE *bill = fopen(filename, "r"); //open bill file to print bill
        if (bill != NULL)
        {
          char line[128];
          while (fgets(line, sizeof line, bill) != NULL)
          {
            //set count to zero each row,
            count = 0;

            token = strtok(line, s); //breaks string by "," (s=",")

            while (token != NULL)
            {
              switch (count)
              {
              case 0:
                //item name
                printf("%-40s", token);
                break;
              case 1:
                //unit price
                printf("%15s", token);
                break;
              case 2:
                //qty
                printf("%17s", token);
                break;
              case 3:
                // amount
                printf("%18s\n", token);
                break;

            
               
              }

              count++;
              token = strtok(NULL, s); 
            }
          }
          fclose(bill);
        }
        

        printf("================================================================================================\n");
        printf("Total Amount  :%74.2f", add2);      //print total amount on footer bill
        printf("\nCash Amount   :%74.2f", cash2);
        printf("\nBalance Amount:%74.2f", cash2 - add2);
        printf("\n================================================================================================\n");
        remove("bill"); //delete bill
        footer_bill();

        break;
      }
      

      else //if customer cash amount is equal or higher than total amount
      {
        header_bill();

        printf("\n================================================================================================\n");
        printf("%-40s%15s%17s%17s\n", "Item", "Unit Price", "Qty", "Amount");
        printf("%55s%34s\n", "(Rs.)", "(Rs.)");
        printf("================================================================================================\n\n");

        const char filename[] = "bill";
        FILE *bill = fopen(filename, "r");
        if (bill != NULL)
        {
          char line[128];
          while (fgets(line, sizeof line, bill) != NULL)
          {
            //set count to zero each row,
            count = 0;

            token = strtok(line, s);
        

            while (token != NULL)
            {
              switch (count)
              {
              case 0:
                //item name
                printf("%-40s", token);
                break;
              case 1:
                //unit price
                printf("%15s", token);
                break;
              case 2:
                //qty
                printf("%17s", token);
                break;
              case 3:
                //total amount
                printf("%18s\n", token);
                break;

              default:
                printf("ERROR");
              }

              count++;
              token = strtok(NULL, s);
            }
          }
          fclose(bill);
        }

        printf("================================================================================================\n");
        printf("Total Amount  :%74.2f", add2);
        printf("\nCash Amount   :%74.2f", cash);
        printf("\nBalance Amount:%74.2f", cash - add2);
        printf("\n================================================================================================\n");
        remove("bill");
        footer_bill();

        break;
      }
    }

    printf("Enter quantity of item:"); //if customer enter a correct item code then quentityof item
    scanf("%d", &qunt);

    const char filename[] = "item_details";
    FILE *file = fopen(filename, "r");

    if (file != NULL)
    {
      char line[128];  //or other suitable maximum line size
      while (fgets(line, sizeof line, file) != NULL) // read a line
      {
        //set count to zero each row,
        count = 0;
        //get first token item code
        token = strtok(line, s);
        //if both strings are same,
        if (!strcmp(token, item_code_id))
        {
          //then go to other tokens
          while (token != NULL)
          {
            switch (count)
            {
            case 1:
              //item name when 

              bill = fopen("bill", "a");
              fprintf(bill, "%s,", token); // enter item name to bill file
              fclose(bill);
              printf("\nname:%s", token);
              break;

            case 2:
              strcpy(copy1,token);

              // item price

              double x = atof(copy1);

              bill = fopen("bill", "a");
              fprintf(bill, "%.2f,", x); //enter unit price to bill file
              fclose(bill);
              
              printf("\nUnit price  :           %67.2f", x);
              add = x * qunt;

              bill = fopen("bill", "a");

              fprintf(bill, "%d,", qunt); //enter quentity to bill file
              fclose(bill);
              add2 = add2 + add;

              bill = fopen("bill", "a");
              fprintf(bill, "%.2f\n", add); // enter amount to bill file
              fclose(bill);

              
              printf("\nqty         :           %67d", qunt);
              printf("\n................................................................................................");
              printf("\nAmount(Rs)  :           %67.2f\n", add);
              printf("................................................................................................");
              break;

            default:
              printf("\n");
            }

            count++;
            token = strtok(NULL, s);
          }
        }
      }
      fclose(file);
    }
  }
  main();
}


void shop_details()
{
  //edit shop details
  char shop_name[100];
  char address[100];
  char tel[15];

  FILE *shop_details;
  shop_details = fopen("shop_details", "w"); // open shop details file as writting mode

  printf("Enter shop name :");
  scanf("%s", shop_name);

  printf("\nEnter shop address :");
  scanf("%s", address);

  printf("\nEnter shop Tel_No :");
  scanf("%s", tel);
  // print to file
  fprintf(shop_details, "%s\n", shop_name);
  fprintf(shop_details, "%s\n", address);
  fprintf(shop_details, "%s\n", tel);

  fclose(shop_details);

  main();
}


void cashier_details()
{
  //cashier details
  char cashier_name[100];
  int date;
  int month;
  int year;

  FILE *cashier;
  cashier = fopen("cashier", "w"); // open cashier file writting mode

  printf("Enter cashier name:");
  scanf("%s", cashier_name);
  fprintf(cashier, "%s\n", cashier_name);

  // getting date 
  printf("\nSet date-->");
  printf("\nEnter date :");
  scanf("%d", &date);
  printf("\nEnter month:");
  scanf("%d", &month);
  printf("\nEnter year :");
  scanf("%d", &year);
  fprintf(cashier, "%d\n %d\n %d\n", date, month, year);

  fclose(cashier);

  main();
}


void header_bill() // bill header(shop name,address,t.p)
{
  char shop_name[100];
  char address[100];
  char tel[15];

  FILE *shop_details;
  shop_details = fopen("shop_details", "r");
  fscanf(shop_details, "%s%s%s", shop_name, address, tel);
  printf("\n\n\n%96s\n%96s\n%96s\n", shop_name, address, tel);
}

void footer_bill() // bill footer (cashier name,date,greeting)
{
  char cashier_name[100];
  int date;
  int month;
  int year;

  FILE *cashier;
  cashier = fopen("cashier", "r");
  fscanf(cashier, "%s%d%d%d", cashier_name, &date, &month, &year);
  printf("Cashier :%s\nDate    :%d/%d/%d\n\nTHANK YOU,COME AGAIN !!!\n\n\n\n", cashier_name, date, month, year);
}


void list() //show  item list and price
{


  int count = 0;
  const char s[2] = ",";
  char *token;

  double x;
  printf("\n---------------------------------------- OUR PRICE ----------------------------------------\n");
  printf("\n*******************************************************************************************\n");
  printf("%-4s%60s%18s\n", "Item Code", "Item", "Unit Price");
  printf("%87s\n", "(Rs.)");
  printf("*******************************************************************************************\n\n");

  while (1)
  {

    const char filename[] = "item_details";
    FILE *flist = fopen(filename, "r");
    if (flist != NULL)
    {
      char line[128];
      while (fgets(line, sizeof line, flist) != NULL)
      {

        count = 0;

        token = strtok(line, s);

        while (token != NULL)
        {
          switch (count)
          {
          case 0:

            printf("%-4s", token); // item code
            break;
          case 1:

            printf("%65s", token); // item name
            break;

          case 2:
            x = atof(token);
            printf("%18.2f\n", x); // unit price
            break;

          default:
            printf("ERROR");
          }

          count++;
          token = strtok(NULL, s);
        }
        printf("___________________________________________________________________________________________\n");
      }
      fclose(flist);
      break;
    }
  }
}