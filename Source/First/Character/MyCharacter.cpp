// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    UCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

    UCamera->SetupAttachment(RootComponent);
    UCamera->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    check(PlayerInputComponent);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::StopJumping);
}

void AMyCharacter::MoveForward(float Value)
{
    if (Value != 0.f)
    {
        AddMovementInput(GetActorForwardVector(), Value);
    }

//     if (Value != 0.0f)
//     {
//         // find out which way is forward
//         const FRotator Rotation = GetControlRotation();
//         const FRotator YawRotation(0, Rotation.Yaw, 0);
// 
//         // get forward vector
//         const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
//         AddMovementInput(Direction, Value);
//     }
}

void AMyCharacter::MoveRight(float Value)
{
    if (Value != 0.f)
    {
        AddMovementInput(GetActorRightVector(), Value);
    }
}

// AMyProjectCharacter::AMyProjectCharacter()
// {
//     // Set size for collision capsule
//     GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
// 
//     // set our turn rates for input
//     BaseTurnRate = 45.f;
//     BaseLookUpRate = 45.f;
// 
//     // Don't rotate when the controller rotates. Let that just affect the camera.
//     bUseControllerRotationPitch = false;
//     bUseControllerRotationYaw = false;
//     bUseControllerRotationRoll = false;
// 
//     // Configure character movement
//     GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
//     GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
//     GetCharacterMovement()->JumpZVelocity = 600.f;
//     GetCharacterMovement()->AirControl = 0.2f;
// 
//     // Create a camera boom (pulls in towards the player if there is a collision)
//     CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
//     CameraBoom->SetupAttachment(RootComponent);
//     CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
//     CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
// 
//                                                 // Create a follow camera
//     FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
//     FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
//     FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
// 
//                                                    // Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
//                                                    // are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
// }
// 
// //////////////////////////////////////////////////////////////////////////
// // Input
// 
// void AMyProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
// {
//     // Set up gameplay key bindings
//     check(PlayerInputComponent);
//     PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
//     PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
// 
//     PlayerInputComponent->BindAxis("MoveForward", this, &AMyProjectCharacter::MoveForward);
//     PlayerInputComponent->BindAxis("MoveRight", this, &AMyProjectCharacter::MoveRight);
// 
//     // We have 2 versions of the rotation bindings to handle different kinds of devices differently
//     // "turn" handles devices that provide an absolute delta, such as a mouse.
//     // "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
//     PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
//     PlayerInputComponent->BindAxis("TurnRate", this, &AMyProjectCharacter::TurnAtRate);
//     PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
//     PlayerInputComponent->BindAxis("LookUpRate", this, &AMyProjectCharacter::LookUpAtRate);
// 
//     // handle touch devices
//     PlayerInputComponent->BindTouch(IE_Pressed, this, &AMyProjectCharacter::TouchStarted);
//     PlayerInputComponent->BindTouch(IE_Released, this, &AMyProjectCharacter::TouchStopped);
// 
//     // VR headset functionality
//     PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AMyProjectCharacter::OnResetVR);
// }
// 
// 
// void AMyProjectCharacter::OnResetVR()
// {
//     UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
// }
// 
// void AMyProjectCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
// {
//     Jump();
// }
// 
// void AMyProjectCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
// {
//     StopJumping();
// }
// 
// void AMyProjectCharacter::TurnAtRate(float Rate)
// {
//     // calculate delta for this frame from the rate information
//     AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
// }
// 
// void AMyProjectCharacter::LookUpAtRate(float Rate)
// {
//     // calculate delta for this frame from the rate information
//     AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
// }
// 
// void AMyProjectCharacter::MoveForward(float Value)
// {
//     if ((Controller != NULL) && (Value != 0.0f))
//     {
//         // find out which way is forward
//         const FRotator Rotation = Controller->GetControlRotation();
//         const FRotator YawRotation(0, Rotation.Yaw, 0);
// 
//         // get forward vector
//         const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
//         AddMovementInput(Direction, Value);
//     }
// }
// 
// void AMyProjectCharacter::MoveRight(float Value)
// {
//     if ((Controller != NULL) && (Value != 0.0f))
//     {
//         // find out which way is right
//         const FRotator Rotation = Controller->GetControlRotation();
//         const FRotator YawRotation(0, Rotation.Yaw, 0);
// 
//         // get right vector 
//         const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
//         // add movement in that direction
//         AddMovementInput(Direction, Value);
//     }
// }

