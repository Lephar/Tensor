package org.arch.tensor

import android.os.Bundle
import android.content.res.AssetManager
import androidx.appcompat.app.AppCompatActivity
import org.arch.tensor.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {
    external fun initializeTensor(assets: AssetManager): Unit
    external fun runTensor(string: String): Unit
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

        binding.button.setOnClickListener {
            binding.button.isEnabled = false
            runTensor(binding.text.text.toString())
            binding.button.isEnabled = true
        }

        binding.text.isEnabled = true
        binding.button.isEnabled = true
    }

    override fun onDestroy() {
        super.onDestroy()

        destroyTensor();
    }
}