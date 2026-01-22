package org.arch.tensor

import android.os.Bundle
import android.content.res.AssetManager
import androidx.appcompat.app.AppCompatActivity
import org.arch.tensor.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {
    external fun initializeTensor(assets: AssetManager): Unit
    external fun destroyTensor(): Unit

    private lateinit var binding: ActivityMainBinding

    companion object {
        init {
            System.loadLibrary("tensor")
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        initializeTensor(assets);
    }

    override fun onDestroy() {
        super.onDestroy()

        destroyTensor();
    }
}