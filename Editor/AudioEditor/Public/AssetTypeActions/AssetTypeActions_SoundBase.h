// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

struct FAssetData;
class USoundBase;

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AUDIOEDITOR_API FAssetTypeActions_SoundBase : public FAssetTypeActions_Base
{
public:
	// IAssetTypeActions Implementation
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_SoundBase", "Sound Base"); }
	virtual FColor GetTypeColor() const override { return FColor(97, 85, 212); }
	virtual UClass* GetSupportedClass() const override;
	virtual bool HasActions ( const TArray<UObject*>& InObjects ) const override { return true; }
	virtual void GetActions(const TArray<UObject*>& InObjects, struct FToolMenuSection& Section) override;
	virtual void AssetsActivated( const TArray<UObject*>& InObjects, EAssetTypeActivationMethod::Type ActivationType ) override;
	virtual bool AssetsActivatedOverride(const TArray<UObject*>& InObjects, EAssetTypeActivationMethod::Type ActivationType) override;
	virtual uint32 GetCategories() override { return EAssetTypeCategories::Sounds; }
	virtual bool CanFilter() override { return false; }
	virtual TSharedPtr<SWidget> GetThumbnailOverlay(const FAssetData& AssetData) const override;

protected:
	/** Plays the specified sound wave */
	void PlaySound(USoundBase* Sound) const;

	/** Stops any currently playing sounds */
	void StopSound() const;

	/** Return true if the specified sound is playing */
	bool IsSoundPlaying(USoundBase* Sound) const;

	/** Return true if the specified asset's sound is playing */
	bool IsSoundPlaying(const FAssetData& AssetData) const;

private:
	/** Handler for when PlaySound is selected */
	void ExecutePlaySound(TArray<TWeakObjectPtr<USoundBase>> Objects) const;

	/** Handler for when StopSound is selected */
	void ExecuteStopSound(TArray<TWeakObjectPtr<USoundBase>> Objects) const;

	/** Returns true if only one sound is selected to play */
	bool CanExecutePlayCommand(TArray<TWeakObjectPtr<USoundBase>> Objects) const;

	/** Handler for Mute is selected  */
	void ExecuteMuteSound(TArray<TWeakObjectPtr<USoundBase>> Objects) const;
	
	/** Handler for Solo is selected  */
	void ExecuteSoloSound(TArray<TWeakObjectPtr<USoundBase>> Objects) const;

	/** Returns true if the mute state is set.  */
	bool IsActionCheckedMute(TArray<TWeakObjectPtr<USoundBase>> Objects) const;

	/** Returns true if the solo state is set.  */
	bool IsActionCheckedSolo(TArray<TWeakObjectPtr<USoundBase>> Objects) const;

	/** Returns true if its possible to mute a sound */
	bool CanExecuteMuteCommand(TArray<TWeakObjectPtr<USoundBase>> Objects) const;
	
	/** Returns true if its possible to solo a sound */
	bool CanExecuteSoloCommand(TArray<TWeakObjectPtr<USoundBase>> Objects) const;
};
PRAGMA_ENABLE_DEPRECATION_WARNINGS
